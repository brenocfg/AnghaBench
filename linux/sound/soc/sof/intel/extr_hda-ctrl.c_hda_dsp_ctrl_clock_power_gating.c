#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_sof_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_DSP_HDA_BAR ; 
 int /*<<< orphan*/  HDA_VS_INTEL_EM2 ; 
 int /*<<< orphan*/  HDA_VS_INTEL_EM2_L1SEN ; 
 int /*<<< orphan*/  PCI_CGCTL ; 
 int /*<<< orphan*/  PCI_CGCTL_ADSPDCGE ; 
 int /*<<< orphan*/  PCI_PGCTL ; 
 int /*<<< orphan*/  PCI_PGCTL_ADSPPGD ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_pci_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hda_dsp_ctrl_clock_power_gating(struct snd_sof_dev *sdev, bool enable)
{
	u32 val;

	/* enable/disable audio dsp clock gating */
	val = enable ? PCI_CGCTL_ADSPDCGE : 0;
	snd_sof_pci_update_bits(sdev, PCI_CGCTL, PCI_CGCTL_ADSPDCGE, val);

	/* enable/disable DMI Link L1 support */
	val = enable ? HDA_VS_INTEL_EM2_L1SEN : 0;
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, HDA_VS_INTEL_EM2,
				HDA_VS_INTEL_EM2_L1SEN, val);

	/* enable/disable audio dsp power gating */
	val = enable ? 0 : PCI_PGCTL_ADSPPGD;
	snd_sof_pci_update_bits(sdev, PCI_PGCTL, PCI_PGCTL_ADSPPGD, val);

	return 0;
}