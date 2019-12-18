#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct soc_tplg {int /*<<< orphan*/  dev; int /*<<< orphan*/  index; scalar_t__ pos; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
struct soc_enum {long private_value; struct soc_enum* name; TYPE_2__ dobj; int /*<<< orphan*/  mask; int /*<<< orphan*/  items; void* shift_r; void* shift_l; int /*<<< orphan*/  reg; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;
struct TYPE_8__ {int /*<<< orphan*/  info; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; TYPE_3__ ops; int /*<<< orphan*/  access; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct snd_soc_tplg_enum_control {TYPE_4__ hdr; int /*<<< orphan*/  mask; int /*<<< orphan*/  items; int /*<<< orphan*/  channel; TYPE_1__ priv; } ;
struct snd_soc_tplg_ctl_hdr {int dummy; } ;
struct snd_kcontrol_new {long private_value; struct snd_kcontrol_new* name; TYPE_2__ dobj; int /*<<< orphan*/  mask; int /*<<< orphan*/  items; void* shift_r; void* shift_l; int /*<<< orphan*/  reg; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_CHMAP_FL ; 
 int /*<<< orphan*/  SNDRV_CHMAP_FR ; 
 scalar_t__ SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
#define  SND_SOC_TPLG_CTL_ENUM 132 
#define  SND_SOC_TPLG_CTL_ENUM_VALUE 131 
#define  SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE 130 
#define  SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE 129 
#define  SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct soc_enum* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct soc_enum*) ; 
 struct soc_enum* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct soc_enum* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_control_err (struct soc_tplg*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int soc_tplg_denum_create_texts (struct soc_enum*,struct snd_soc_tplg_enum_control*) ; 
 int soc_tplg_denum_create_values (struct soc_enum*,struct snd_soc_tplg_enum_control*) ; 
 int /*<<< orphan*/  soc_tplg_denum_remove_texts (struct soc_enum*) ; 
 int /*<<< orphan*/  soc_tplg_denum_remove_values (struct soc_enum*) ; 
 int soc_tplg_init_kcontrol (struct soc_tplg*,struct soc_enum*,struct snd_soc_tplg_ctl_hdr*) ; 
 int soc_tplg_kcontrol_bind_io (TYPE_4__*,struct soc_enum*,struct soc_tplg*) ; 
 scalar_t__ strnlen (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tplc_chan_get_reg (struct soc_tplg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* tplc_chan_get_shift (struct soc_tplg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_kcontrol_new *soc_tplg_dapm_widget_denum_create(
	struct soc_tplg *tplg, int num_kcontrols)
{
	struct snd_kcontrol_new *kc;
	struct snd_soc_tplg_enum_control *ec;
	struct soc_enum *se;
	int i, err;

	kc = kcalloc(num_kcontrols, sizeof(*kc), GFP_KERNEL);
	if (kc == NULL)
		return NULL;

	for (i = 0; i < num_kcontrols; i++) {
		ec = (struct snd_soc_tplg_enum_control *)tplg->pos;
		/* validate kcontrol */
		if (strnlen(ec->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			    SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			goto err_se;

		se = kzalloc(sizeof(*se), GFP_KERNEL);
		if (se == NULL)
			goto err_se;

		tplg->pos += (sizeof(struct snd_soc_tplg_enum_control) +
				ec->priv.size);

		dev_dbg(tplg->dev, " adding DAPM widget enum control %s\n",
			ec->hdr.name);

		kc[i].private_value = (long)se;
		kc[i].name = kstrdup(ec->hdr.name, GFP_KERNEL);
		if (kc[i].name == NULL)
			goto err_se;
		kc[i].iface = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc[i].access = ec->hdr.access;

		/* we only support FL/FR channel mapping atm */
		se->reg = tplc_chan_get_reg(tplg, ec->channel, SNDRV_CHMAP_FL);
		se->shift_l = tplc_chan_get_shift(tplg, ec->channel,
						  SNDRV_CHMAP_FL);
		se->shift_r = tplc_chan_get_shift(tplg, ec->channel,
						  SNDRV_CHMAP_FR);

		se->items = ec->items;
		se->mask = ec->mask;
		se->dobj.index = tplg->index;

		switch (le32_to_cpu(ec->hdr.ops.info)) {
		case SND_SOC_TPLG_CTL_ENUM_VALUE:
		case SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE:
			err = soc_tplg_denum_create_values(se, ec);
			if (err < 0) {
				dev_err(tplg->dev, "ASoC: could not create values for %s\n",
					ec->hdr.name);
				goto err_se;
			}
			/* fall through */
		case SND_SOC_TPLG_CTL_ENUM:
		case SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE:
		case SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT:
			err = soc_tplg_denum_create_texts(se, ec);
			if (err < 0) {
				dev_err(tplg->dev, "ASoC: could not create texts for %s\n",
					ec->hdr.name);
				goto err_se;
			}
			break;
		default:
			dev_err(tplg->dev, "ASoC: invalid enum control type %d for %s\n",
				ec->hdr.ops.info, ec->hdr.name);
			goto err_se;
		}

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&ec->hdr, &kc[i], tplg);
		if (err) {
			soc_control_err(tplg, &ec->hdr, ec->hdr.name);
			goto err_se;
		}

		/* pass control to driver for optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc[i],
			(struct snd_soc_tplg_ctl_hdr *)ec);
		if (err < 0) {
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				ec->hdr.name);
			goto err_se;
		}
	}

	return kc;

err_se:
	for (; i >= 0; i--) {
		/* free values and texts */
		se = (struct soc_enum *)kc[i].private_value;

		if (se) {
			soc_tplg_denum_remove_values(se);
			soc_tplg_denum_remove_texts(se);
		}

		kfree(se);
		kfree(kc[i].name);
	}
	kfree(kc);

	return NULL;
}