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
struct soc_tplg {scalar_t__ pass; int pos; int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_hdr {int /*<<< orphan*/  payload_size; int /*<<< orphan*/  count; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  info; } ;
struct snd_soc_tplg_ctl_hdr {TYPE_1__ ops; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
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
 scalar_t__ SOC_TPLG_PASS_MIXER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_bind_err (struct soc_tplg*,struct snd_soc_tplg_ctl_hdr*,int) ; 
 int /*<<< orphan*/  soc_tplg_dbytes_create (struct soc_tplg*,int,int) ; 
 int /*<<< orphan*/  soc_tplg_denum_create (struct soc_tplg*,int,int) ; 
 int /*<<< orphan*/  soc_tplg_dmixer_create (struct soc_tplg*,int,int) ; 
 int /*<<< orphan*/  soc_tplg_get_offset (struct soc_tplg*) ; 

__attribute__((used)) static int soc_tplg_kcontrol_elems_load(struct soc_tplg *tplg,
	struct snd_soc_tplg_hdr *hdr)
{
	struct snd_soc_tplg_ctl_hdr *control_hdr;
	int i;

	if (tplg->pass != SOC_TPLG_PASS_MIXER) {
		tplg->pos += le32_to_cpu(hdr->size) +
			le32_to_cpu(hdr->payload_size);
		return 0;
	}

	dev_dbg(tplg->dev, "ASoC: adding %d kcontrols at 0x%lx\n", hdr->count,
		soc_tplg_get_offset(tplg));

	for (i = 0; i < le32_to_cpu(hdr->count); i++) {

		control_hdr = (struct snd_soc_tplg_ctl_hdr *)tplg->pos;

		if (le32_to_cpu(control_hdr->size) != sizeof(*control_hdr)) {
			dev_err(tplg->dev, "ASoC: invalid control size\n");
			return -EINVAL;
		}

		switch (le32_to_cpu(control_hdr->ops.info)) {
		case SND_SOC_TPLG_CTL_VOLSW:
		case SND_SOC_TPLG_CTL_STROBE:
		case SND_SOC_TPLG_CTL_VOLSW_SX:
		case SND_SOC_TPLG_CTL_VOLSW_XR_SX:
		case SND_SOC_TPLG_CTL_RANGE:
		case SND_SOC_TPLG_DAPM_CTL_VOLSW:
		case SND_SOC_TPLG_DAPM_CTL_PIN:
			soc_tplg_dmixer_create(tplg, 1,
					       le32_to_cpu(hdr->payload_size));
			break;
		case SND_SOC_TPLG_CTL_ENUM:
		case SND_SOC_TPLG_CTL_ENUM_VALUE:
		case SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE:
		case SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT:
		case SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE:
			soc_tplg_denum_create(tplg, 1,
					      le32_to_cpu(hdr->payload_size));
			break;
		case SND_SOC_TPLG_CTL_BYTES:
			soc_tplg_dbytes_create(tplg, 1,
					       le32_to_cpu(hdr->payload_size));
			break;
		default:
			soc_bind_err(tplg, control_hdr, i);
			return -EINVAL;
		}
	}

	return 0;
}