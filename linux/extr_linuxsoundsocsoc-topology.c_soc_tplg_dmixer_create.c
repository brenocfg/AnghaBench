#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct soc_tplg {TYPE_4__* comp; int /*<<< orphan*/  dev; int /*<<< orphan*/  ops; int /*<<< orphan*/  index; scalar_t__ pos; } ;
struct TYPE_9__ {int /*<<< orphan*/  kcontrol; } ;
struct TYPE_10__ {int /*<<< orphan*/  list; TYPE_2__ control; int /*<<< orphan*/  type; int /*<<< orphan*/  ops; int /*<<< orphan*/  index; } ;
struct soc_mixer_control {TYPE_3__ dobj; int /*<<< orphan*/  platform_max; int /*<<< orphan*/  invert; int /*<<< orphan*/  min; int /*<<< orphan*/  max; void* rshift; void* shift; void* rreg; void* reg; } ;
struct TYPE_12__ {unsigned int name; int /*<<< orphan*/  access; } ;
struct TYPE_8__ {scalar_t__ size; } ;
struct snd_soc_tplg_mixer_control {TYPE_5__ hdr; int /*<<< orphan*/  platform_max; int /*<<< orphan*/  invert; int /*<<< orphan*/  min; int /*<<< orphan*/  max; int /*<<< orphan*/  channel; TYPE_1__ priv; } ;
struct snd_soc_tplg_ctl_hdr {int dummy; } ;
struct snd_kcontrol_new {unsigned int name; long private_value; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;
typedef  int /*<<< orphan*/  kc ;
struct TYPE_11__ {int /*<<< orphan*/  dobj_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNDRV_CHMAP_FL ; 
 int /*<<< orphan*/  SNDRV_CHMAP_FR ; 
 scalar_t__ SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  SND_SOC_DOBJ_MIXER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct soc_mixer_control*) ; 
 struct soc_mixer_control* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct snd_kcontrol_new*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soc_control_err (struct soc_tplg*,TYPE_5__*,unsigned int) ; 
 int soc_tplg_add_kcontrol (struct soc_tplg*,struct snd_kcontrol_new*,int /*<<< orphan*/ *) ; 
 scalar_t__ soc_tplg_check_elem_count (struct soc_tplg*,int,unsigned int,size_t,char*) ; 
 int /*<<< orphan*/  soc_tplg_create_tlv (struct soc_tplg*,struct snd_kcontrol_new*,TYPE_5__*) ; 
 int /*<<< orphan*/  soc_tplg_free_tlv (struct soc_tplg*,struct snd_kcontrol_new*) ; 
 int soc_tplg_init_kcontrol (struct soc_tplg*,struct snd_kcontrol_new*,struct snd_soc_tplg_ctl_hdr*) ; 
 int soc_tplg_kcontrol_bind_io (TYPE_5__*,struct snd_kcontrol_new*,struct soc_tplg*) ; 
 scalar_t__ strnlen (unsigned int,scalar_t__) ; 
 void* tplc_chan_get_reg (struct soc_tplg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* tplc_chan_get_shift (struct soc_tplg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_tplg_dmixer_create(struct soc_tplg *tplg, unsigned int count,
	size_t size)
{
	struct snd_soc_tplg_mixer_control *mc;
	struct soc_mixer_control *sm;
	struct snd_kcontrol_new kc;
	int i, err;

	if (soc_tplg_check_elem_count(tplg,
		sizeof(struct snd_soc_tplg_mixer_control),
		count, size, "mixers")) {

		dev_err(tplg->dev, "ASoC: invalid count %d for controls\n",
			count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		mc = (struct snd_soc_tplg_mixer_control *)tplg->pos;

		/* validate kcontrol */
		if (strnlen(mc->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			return -EINVAL;

		sm = kzalloc(sizeof(*sm), GFP_KERNEL);
		if (sm == NULL)
			return -ENOMEM;
		tplg->pos += (sizeof(struct snd_soc_tplg_mixer_control) +
			mc->priv.size);

		dev_dbg(tplg->dev,
			"ASoC: adding mixer kcontrol %s with access 0x%x\n",
			mc->hdr.name, mc->hdr.access);

		memset(&kc, 0, sizeof(kc));
		kc.name = mc->hdr.name;
		kc.private_value = (long)sm;
		kc.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc.access = mc->hdr.access;

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
		sm->dobj.ops = tplg->ops;
		sm->dobj.type = SND_SOC_DOBJ_MIXER;
		INIT_LIST_HEAD(&sm->dobj.list);

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&mc->hdr, &kc, tplg);
		if (err) {
			soc_control_err(tplg, &mc->hdr, mc->hdr.name);
			kfree(sm);
			continue;
		}

		/* pass control to driver for optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc,
			(struct snd_soc_tplg_ctl_hdr *) mc);
		if (err < 0) {
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				mc->hdr.name);
			kfree(sm);
			continue;
		}

		/* create any TLV data */
		soc_tplg_create_tlv(tplg, &kc, &mc->hdr);

		/* register control here */
		err = soc_tplg_add_kcontrol(tplg, &kc,
			&sm->dobj.control.kcontrol);
		if (err < 0) {
			dev_err(tplg->dev, "ASoC: failed to add %s\n",
				mc->hdr.name);
			soc_tplg_free_tlv(tplg, &kc);
			kfree(sm);
			continue;
		}

		list_add(&sm->dobj.list, &tplg->comp->dobj_list);
	}

	return 0;
}