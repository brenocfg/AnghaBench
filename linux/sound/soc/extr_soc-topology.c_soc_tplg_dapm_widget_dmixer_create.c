#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct soc_tplg {int /*<<< orphan*/  dev; int /*<<< orphan*/  index; scalar_t__ pos; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; int /*<<< orphan*/  index; } ;
struct soc_mixer_control {long private_value; struct soc_mixer_control* name; TYPE_2__ dobj; int /*<<< orphan*/  platform_max; int /*<<< orphan*/  invert; int /*<<< orphan*/  min; int /*<<< orphan*/  max; void* rshift; void* shift; void* rreg; void* reg; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  access; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct snd_soc_tplg_mixer_control {TYPE_3__ hdr; int /*<<< orphan*/  platform_max; int /*<<< orphan*/  invert; int /*<<< orphan*/  min; int /*<<< orphan*/  max; int /*<<< orphan*/  channel; TYPE_1__ priv; } ;
struct snd_soc_tplg_ctl_hdr {int dummy; } ;
struct snd_kcontrol_new {long private_value; struct snd_kcontrol_new* name; TYPE_2__ dobj; int /*<<< orphan*/  platform_max; int /*<<< orphan*/  invert; int /*<<< orphan*/  min; int /*<<< orphan*/  max; void* rshift; void* shift; void* rreg; void* reg; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNDRV_CHMAP_FL ; 
 int /*<<< orphan*/  SNDRV_CHMAP_FR ; 
 scalar_t__ SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct soc_mixer_control* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct soc_mixer_control*) ; 
 struct soc_mixer_control* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct soc_mixer_control* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_control_err (struct soc_tplg*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_tplg_create_tlv (struct soc_tplg*,struct soc_mixer_control*,TYPE_3__*) ; 
 int /*<<< orphan*/  soc_tplg_free_tlv (struct soc_tplg*,struct soc_mixer_control*) ; 
 int soc_tplg_init_kcontrol (struct soc_tplg*,struct soc_mixer_control*,struct snd_soc_tplg_ctl_hdr*) ; 
 int soc_tplg_kcontrol_bind_io (TYPE_3__*,struct soc_mixer_control*,struct soc_tplg*) ; 
 scalar_t__ strnlen (int /*<<< orphan*/ ,scalar_t__) ; 
 void* tplc_chan_get_reg (struct soc_tplg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* tplc_chan_get_shift (struct soc_tplg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_kcontrol_new *soc_tplg_dapm_widget_dmixer_create(
	struct soc_tplg *tplg, int num_kcontrols)
{
	struct snd_kcontrol_new *kc;
	struct soc_mixer_control *sm;
	struct snd_soc_tplg_mixer_control *mc;
	int i, err;

	kc = kcalloc(num_kcontrols, sizeof(*kc), GFP_KERNEL);
	if (kc == NULL)
		return NULL;

	for (i = 0; i < num_kcontrols; i++) {
		mc = (struct snd_soc_tplg_mixer_control *)tplg->pos;

		/* validate kcontrol */
		if (strnlen(mc->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			goto err_sm;

		sm = kzalloc(sizeof(*sm), GFP_KERNEL);
		if (sm == NULL)
			goto err_sm;

		tplg->pos += (sizeof(struct snd_soc_tplg_mixer_control) +
			      le32_to_cpu(mc->priv.size));

		dev_dbg(tplg->dev, " adding DAPM widget mixer control %s at %d\n",
			mc->hdr.name, i);

		kc[i].private_value = (long)sm;
		kc[i].name = kstrdup(mc->hdr.name, GFP_KERNEL);
		if (kc[i].name == NULL)
			goto err_sm;
		kc[i].iface = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc[i].access = mc->hdr.access;

		/* we only support FL/FR channel mapping atm */
		sm->reg = tplc_chan_get_reg(tplg, mc->channel,
			SNDRV_CHMAP_FL);
		sm->rreg = tplc_chan_get_reg(tplg, mc->channel,
			SNDRV_CHMAP_FR);
		sm->shift = tplc_chan_get_shift(tplg, mc->channel,
			SNDRV_CHMAP_FL);
		sm->rshift = tplc_chan_get_shift(tplg, mc->channel,
			SNDRV_CHMAP_FR);

		sm->max = mc->max;
		sm->min = mc->min;
		sm->invert = mc->invert;
		sm->platform_max = mc->platform_max;
		sm->dobj.index = tplg->index;
		INIT_LIST_HEAD(&sm->dobj.list);

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&mc->hdr, &kc[i], tplg);
		if (err) {
			soc_control_err(tplg, &mc->hdr, mc->hdr.name);
			goto err_sm;
		}

		/* create any TLV data */
		soc_tplg_create_tlv(tplg, &kc[i], &mc->hdr);

		/* pass control to driver for optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc[i],
			(struct snd_soc_tplg_ctl_hdr *)mc);
		if (err < 0) {
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				mc->hdr.name);
			soc_tplg_free_tlv(tplg, &kc[i]);
			goto err_sm;
		}
	}
	return kc;

err_sm:
	for (; i >= 0; i--) {
		sm = (struct soc_mixer_control *)kc[i].private_value;
		kfree(sm);
		kfree(kc[i].name);
	}
	kfree(kc);

	return NULL;
}