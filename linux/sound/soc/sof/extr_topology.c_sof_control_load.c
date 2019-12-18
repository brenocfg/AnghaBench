#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dobj {struct snd_sof_control* private; } ;
struct soc_mixer_control {struct snd_soc_dobj dobj; } ;
struct soc_enum {struct snd_soc_dobj dobj; } ;
struct soc_bytes_ext {struct snd_soc_dobj dobj; } ;
struct snd_sof_dev {int /*<<< orphan*/  kcontrol_list; int /*<<< orphan*/  dev; } ;
struct snd_sof_control {int /*<<< orphan*/  list; struct snd_sof_dev* sdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  info; int /*<<< orphan*/  put; int /*<<< orphan*/  get; } ;
struct snd_soc_tplg_ctl_hdr {TYPE_1__ ops; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol_new {scalar_t__ private_value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  SND_SOC_TPLG_CTL_BYTES 140 
#define  SND_SOC_TPLG_CTL_ENUM 139 
#define  SND_SOC_TPLG_CTL_ENUM_VALUE 138 
#define  SND_SOC_TPLG_CTL_RANGE 137 
#define  SND_SOC_TPLG_CTL_STROBE 136 
#define  SND_SOC_TPLG_CTL_VOLSW 135 
#define  SND_SOC_TPLG_CTL_VOLSW_SX 134 
#define  SND_SOC_TPLG_CTL_VOLSW_XR_SX 133 
#define  SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE 132 
#define  SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE 131 
#define  SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT 130 
#define  SND_SOC_TPLG_DAPM_CTL_PIN 129 
#define  SND_SOC_TPLG_DAPM_CTL_VOLSW 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_sof_control*) ; 
 struct snd_sof_control* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int sof_control_load_bytes (struct snd_soc_component*,struct snd_sof_control*,struct snd_kcontrol_new*,struct snd_soc_tplg_ctl_hdr*) ; 
 int sof_control_load_enum (struct snd_soc_component*,struct snd_sof_control*,struct snd_kcontrol_new*,struct snd_soc_tplg_ctl_hdr*) ; 
 int sof_control_load_volume (struct snd_soc_component*,struct snd_sof_control*,struct snd_kcontrol_new*,struct snd_soc_tplg_ctl_hdr*) ; 

__attribute__((used)) static int sof_control_load(struct snd_soc_component *scomp, int index,
			    struct snd_kcontrol_new *kc,
			    struct snd_soc_tplg_ctl_hdr *hdr)
{
	struct soc_mixer_control *sm;
	struct soc_bytes_ext *sbe;
	struct soc_enum *se;
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	struct snd_soc_dobj *dobj;
	struct snd_sof_control *scontrol;
	int ret = -EINVAL;

	dev_dbg(sdev->dev, "tplg: load control type %d name : %s\n",
		hdr->type, hdr->name);

	scontrol = kzalloc(sizeof(*scontrol), GFP_KERNEL);
	if (!scontrol)
		return -ENOMEM;

	scontrol->sdev = sdev;

	switch (le32_to_cpu(hdr->ops.info)) {
	case SND_SOC_TPLG_CTL_VOLSW:
	case SND_SOC_TPLG_CTL_VOLSW_SX:
	case SND_SOC_TPLG_CTL_VOLSW_XR_SX:
		sm = (struct soc_mixer_control *)kc->private_value;
		dobj = &sm->dobj;
		ret = sof_control_load_volume(scomp, scontrol, kc, hdr);
		break;
	case SND_SOC_TPLG_CTL_BYTES:
		sbe = (struct soc_bytes_ext *)kc->private_value;
		dobj = &sbe->dobj;
		ret = sof_control_load_bytes(scomp, scontrol, kc, hdr);
		break;
	case SND_SOC_TPLG_CTL_ENUM:
	case SND_SOC_TPLG_CTL_ENUM_VALUE:
		se = (struct soc_enum *)kc->private_value;
		dobj = &se->dobj;
		ret = sof_control_load_enum(scomp, scontrol, kc, hdr);
		break;
	case SND_SOC_TPLG_CTL_RANGE:
	case SND_SOC_TPLG_CTL_STROBE:
	case SND_SOC_TPLG_DAPM_CTL_VOLSW:
	case SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE:
	case SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT:
	case SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE:
	case SND_SOC_TPLG_DAPM_CTL_PIN:
	default:
		dev_warn(sdev->dev, "control type not supported %d:%d:%d\n",
			 hdr->ops.get, hdr->ops.put, hdr->ops.info);
		kfree(scontrol);
		return 0;
	}

	dobj->private = scontrol;
	list_add(&scontrol->list, &sdev->kcontrol_list);
	return ret;
}