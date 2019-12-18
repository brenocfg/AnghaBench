#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct soc_tplg {int pos; TYPE_5__* comp; int /*<<< orphan*/  dev; int /*<<< orphan*/  ops; int /*<<< orphan*/  index; } ;
struct TYPE_10__ {int /*<<< orphan*/  kcontrol; } ;
struct TYPE_11__ {int /*<<< orphan*/  list; TYPE_3__ control; int /*<<< orphan*/  ops; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;
struct soc_enum {int mask; TYPE_4__ dobj; void* shift_r; void* shift_l; int /*<<< orphan*/  reg; } ;
struct TYPE_9__ {int /*<<< orphan*/  info; } ;
struct TYPE_13__ {unsigned int name; TYPE_2__ ops; int /*<<< orphan*/  access; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct snd_soc_tplg_enum_control {TYPE_6__ hdr; int /*<<< orphan*/  mask; int /*<<< orphan*/  channel; int /*<<< orphan*/  items; TYPE_1__ priv; } ;
struct snd_soc_tplg_ctl_hdr {int dummy; } ;
struct snd_kcontrol_new {unsigned int name; long private_value; int access; int /*<<< orphan*/  iface; } ;
typedef  int /*<<< orphan*/  kc ;
struct TYPE_12__ {int /*<<< orphan*/  dobj_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNDRV_CHMAP_FL ; 
 scalar_t__ SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  SND_SOC_DOBJ_ENUM ; 
#define  SND_SOC_TPLG_CTL_ENUM 132 
#define  SND_SOC_TPLG_CTL_ENUM_VALUE 131 
#define  SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE 130 
#define  SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE 129 
#define  SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  kfree (struct soc_enum*) ; 
 struct soc_enum* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct snd_kcontrol_new*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soc_control_err (struct soc_tplg*,TYPE_6__*,unsigned int) ; 
 int soc_tplg_add_kcontrol (struct soc_tplg*,struct snd_kcontrol_new*,int /*<<< orphan*/ *) ; 
 scalar_t__ soc_tplg_check_elem_count (struct soc_tplg*,int,unsigned int,size_t,char*) ; 
 int soc_tplg_denum_create_texts (struct soc_enum*,struct snd_soc_tplg_enum_control*) ; 
 int soc_tplg_denum_create_values (struct soc_enum*,struct snd_soc_tplg_enum_control*) ; 
 int soc_tplg_init_kcontrol (struct soc_tplg*,struct snd_kcontrol_new*,struct snd_soc_tplg_ctl_hdr*) ; 
 int soc_tplg_kcontrol_bind_io (TYPE_6__*,struct snd_kcontrol_new*,struct soc_tplg*) ; 
 scalar_t__ strnlen (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  tplc_chan_get_reg (struct soc_tplg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* tplc_chan_get_shift (struct soc_tplg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_tplg_denum_create(struct soc_tplg *tplg, unsigned int count,
	size_t size)
{
	struct snd_soc_tplg_enum_control *ec;
	struct soc_enum *se;
	struct snd_kcontrol_new kc;
	int i, ret, err;

	if (soc_tplg_check_elem_count(tplg,
		sizeof(struct snd_soc_tplg_enum_control),
		count, size, "enums")) {

		dev_err(tplg->dev, "ASoC: invalid count %d for enum controls\n",
			count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		ec = (struct snd_soc_tplg_enum_control *)tplg->pos;

		/* validate kcontrol */
		if (strnlen(ec->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			return -EINVAL;

		se = kzalloc((sizeof(*se)), GFP_KERNEL);
		if (se == NULL)
			return -ENOMEM;

		tplg->pos += (sizeof(struct snd_soc_tplg_enum_control) +
			      le32_to_cpu(ec->priv.size));

		dev_dbg(tplg->dev, "ASoC: adding enum kcontrol %s size %d\n",
			ec->hdr.name, ec->items);

		memset(&kc, 0, sizeof(kc));
		kc.name = ec->hdr.name;
		kc.private_value = (long)se;
		kc.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc.access = le32_to_cpu(ec->hdr.access);

		se->reg = tplc_chan_get_reg(tplg, ec->channel, SNDRV_CHMAP_FL);
		se->shift_l = tplc_chan_get_shift(tplg, ec->channel,
			SNDRV_CHMAP_FL);
		se->shift_r = tplc_chan_get_shift(tplg, ec->channel,
			SNDRV_CHMAP_FL);

		se->mask = le32_to_cpu(ec->mask);
		se->dobj.index = tplg->index;
		se->dobj.type = SND_SOC_DOBJ_ENUM;
		se->dobj.ops = tplg->ops;
		INIT_LIST_HEAD(&se->dobj.list);

		switch (le32_to_cpu(ec->hdr.ops.info)) {
		case SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE:
		case SND_SOC_TPLG_CTL_ENUM_VALUE:
			err = soc_tplg_denum_create_values(se, ec);
			if (err < 0) {
				dev_err(tplg->dev,
					"ASoC: could not create values for %s\n",
					ec->hdr.name);
				kfree(se);
				continue;
			}
			/* fall through */
		case SND_SOC_TPLG_CTL_ENUM:
		case SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE:
		case SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT:
			err = soc_tplg_denum_create_texts(se, ec);
			if (err < 0) {
				dev_err(tplg->dev,
					"ASoC: could not create texts for %s\n",
					ec->hdr.name);
				kfree(se);
				continue;
			}
			break;
		default:
			dev_err(tplg->dev,
				"ASoC: invalid enum control type %d for %s\n",
				ec->hdr.ops.info, ec->hdr.name);
			kfree(se);
			continue;
		}

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&ec->hdr, &kc, tplg);
		if (err) {
			soc_control_err(tplg, &ec->hdr, ec->hdr.name);
			kfree(se);
			continue;
		}

		/* pass control to driver for optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc,
			(struct snd_soc_tplg_ctl_hdr *) ec);
		if (err < 0) {
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				ec->hdr.name);
			kfree(se);
			continue;
		}

		/* register control here */
		ret = soc_tplg_add_kcontrol(tplg,
			&kc, &se->dobj.control.kcontrol);
		if (ret < 0) {
			dev_err(tplg->dev, "ASoC: could not add kcontrol %s\n",
				ec->hdr.name);
			kfree(se);
			continue;
		}

		list_add(&se->dobj.list, &tplg->comp->dobj_list);
	}

	return 0;
}