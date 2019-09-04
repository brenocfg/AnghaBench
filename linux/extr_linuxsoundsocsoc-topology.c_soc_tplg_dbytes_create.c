#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct soc_tplg {TYPE_4__* comp; int /*<<< orphan*/  dev; int /*<<< orphan*/  ops; scalar_t__ pos; } ;
struct TYPE_8__ {int /*<<< orphan*/  kcontrol; } ;
struct TYPE_9__ {int /*<<< orphan*/  list; TYPE_2__ control; int /*<<< orphan*/  ops; int /*<<< orphan*/  type; } ;
struct soc_bytes_ext {TYPE_3__ dobj; int /*<<< orphan*/  max; } ;
struct snd_soc_tplg_ctl_hdr {int dummy; } ;
struct TYPE_11__ {unsigned int name; int /*<<< orphan*/  access; } ;
struct TYPE_7__ {scalar_t__ size; } ;
struct snd_soc_tplg_bytes_control {TYPE_5__ hdr; int /*<<< orphan*/  max; TYPE_1__ priv; } ;
struct snd_kcontrol_new {unsigned int name; long private_value; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;
typedef  int /*<<< orphan*/  kc ;
struct TYPE_10__ {int /*<<< orphan*/  dobj_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  SND_SOC_DOBJ_BYTES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct soc_bytes_ext*) ; 
 struct soc_bytes_ext* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct snd_kcontrol_new*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soc_control_err (struct soc_tplg*,TYPE_5__*,unsigned int) ; 
 int soc_tplg_add_kcontrol (struct soc_tplg*,struct snd_kcontrol_new*,int /*<<< orphan*/ *) ; 
 scalar_t__ soc_tplg_check_elem_count (struct soc_tplg*,int,unsigned int,size_t,char*) ; 
 int soc_tplg_init_kcontrol (struct soc_tplg*,struct snd_kcontrol_new*,struct snd_soc_tplg_ctl_hdr*) ; 
 int soc_tplg_kcontrol_bind_io (TYPE_5__*,struct snd_kcontrol_new*,struct soc_tplg*) ; 
 scalar_t__ strnlen (unsigned int,scalar_t__) ; 

__attribute__((used)) static int soc_tplg_dbytes_create(struct soc_tplg *tplg, unsigned int count,
	size_t size)
{
	struct snd_soc_tplg_bytes_control *be;
	struct soc_bytes_ext *sbe;
	struct snd_kcontrol_new kc;
	int i, err;

	if (soc_tplg_check_elem_count(tplg,
		sizeof(struct snd_soc_tplg_bytes_control), count,
			size, "mixer bytes")) {
		dev_err(tplg->dev, "ASoC: Invalid count %d for byte control\n",
			count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		be = (struct snd_soc_tplg_bytes_control *)tplg->pos;

		/* validate kcontrol */
		if (strnlen(be->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			return -EINVAL;

		sbe = kzalloc(sizeof(*sbe), GFP_KERNEL);
		if (sbe == NULL)
			return -ENOMEM;

		tplg->pos += (sizeof(struct snd_soc_tplg_bytes_control) +
			be->priv.size);

		dev_dbg(tplg->dev,
			"ASoC: adding bytes kcontrol %s with access 0x%x\n",
			be->hdr.name, be->hdr.access);

		memset(&kc, 0, sizeof(kc));
		kc.name = be->hdr.name;
		kc.private_value = (long)sbe;
		kc.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc.access = be->hdr.access;

		sbe->max = be->max;
		sbe->dobj.type = SND_SOC_DOBJ_BYTES;
		sbe->dobj.ops = tplg->ops;
		INIT_LIST_HEAD(&sbe->dobj.list);

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&be->hdr, &kc, tplg);
		if (err) {
			soc_control_err(tplg, &be->hdr, be->hdr.name);
			kfree(sbe);
			continue;
		}

		/* pass control to driver for optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc,
			(struct snd_soc_tplg_ctl_hdr *)be);
		if (err < 0) {
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				be->hdr.name);
			kfree(sbe);
			continue;
		}

		/* register control here */
		err = soc_tplg_add_kcontrol(tplg, &kc,
			&sbe->dobj.control.kcontrol);
		if (err < 0) {
			dev_err(tplg->dev, "ASoC: failed to add %s\n",
				be->hdr.name);
			kfree(sbe);
			continue;
		}

		list_add(&sbe->dobj.list, &tplg->comp->dobj_list);
	}
	return 0;

}