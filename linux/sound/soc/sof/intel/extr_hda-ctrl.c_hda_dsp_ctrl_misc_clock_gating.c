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
 int /*<<< orphan*/  PCI_CGCTL ; 
 int /*<<< orphan*/  PCI_CGCTL_MISCBDCGE_MASK ; 
 int /*<<< orphan*/  snd_sof_pci_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hda_dsp_ctrl_misc_clock_gating(struct snd_sof_dev *sdev, bool enable)
{
	u32 val = enable ? PCI_CGCTL_MISCBDCGE_MASK : 0;

	snd_sof_pci_update_bits(sdev, PCI_CGCTL, PCI_CGCTL_MISCBDCGE_MASK, val);
}