#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct soc_tplg {int /*<<< orphan*/  dev; scalar_t__ pos; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
struct soc_bytes_ext {long private_value; struct soc_bytes_ext* name; TYPE_2__ dobj; int /*<<< orphan*/  max; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;
struct snd_soc_tplg_ctl_hdr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  access; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct snd_soc_tplg_bytes_control {TYPE_3__ hdr; int /*<<< orphan*/  max; TYPE_1__ priv; } ;
struct snd_kcontrol_new {long private_value; struct snd_kcontrol_new* name; TYPE_2__ dobj; int /*<<< orphan*/  max; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct soc_bytes_ext* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct soc_bytes_ext*) ; 
 struct soc_bytes_ext* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct soc_bytes_ext* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_control_err (struct soc_tplg*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int soc_tplg_init_kcontrol (struct soc_tplg*,struct soc_bytes_ext*,struct snd_soc_tplg_ctl_hdr*) ; 
 int soc_tplg_kcontrol_bind_io (TYPE_3__*,struct soc_bytes_ext*,struct soc_tplg*) ; 
 scalar_t__ strnlen (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct snd_kcontrol_new *soc_tplg_dapm_widget_dbytes_create(
	struct soc_tplg *tplg, int num_kcontrols)
{
	struct snd_soc_tplg_bytes_control *be;
	struct soc_bytes_ext *sbe;
	struct snd_kcontrol_new *kc;
	int i, err;

	kc = kcalloc(num_kcontrols, sizeof(*kc), GFP_KERNEL);
	if (!kc)
		return NULL;

	for (i = 0; i < num_kcontrols; i++) {
		be = (struct snd_soc_tplg_bytes_control *)tplg->pos;

		/* validate kcontrol */
		if (strnlen(be->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			goto err_sbe;

		sbe = kzalloc(sizeof(*sbe), GFP_KERNEL);
		if (sbe == NULL)
			goto err_sbe;

		tplg->pos += (sizeof(struct snd_soc_tplg_bytes_control) +
			      le32_to_cpu(be->priv.size));

		dev_dbg(tplg->dev,
			"ASoC: adding bytes kcontrol %s with access 0x%x\n",
			be->hdr.name, be->hdr.access);

		kc[i].private_value = (long)sbe;
		kc[i].name = kstrdup(be->hdr.name, GFP_KERNEL);
		if (kc[i].name == NULL)
			goto err_sbe;
		kc[i].iface = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc[i].access = be->hdr.access;

		sbe->max = be->max;
		INIT_LIST_HEAD(&sbe->dobj.list);

		/* map standard io handlers and check for external handlers */
		err = soc_tplg_kcontrol_bind_io(&be->hdr, &kc[i], tplg);
		if (err) {
			soc_control_err(tplg, &be->hdr, be->hdr.name);
			goto err_sbe;
		}

		/* pass control to driver for optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc[i],
			(struct snd_soc_tplg_ctl_hdr *)be);
		if (err < 0) {
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				be->hdr.name);
			goto err_sbe;
		}
	}

	return kc;

err_sbe:
	for (; i >= 0; i--) {
		sbe = (struct soc_bytes_ext *)kc[i].private_value;
		kfree(sbe);
		kfree(kc[i].name);
	}
	kfree(kc);

	return NULL;
}