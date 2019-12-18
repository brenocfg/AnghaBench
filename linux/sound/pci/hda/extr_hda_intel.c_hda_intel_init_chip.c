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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/ * mlcap; } ;
struct azx {scalar_t__ driver_type; struct pci_dev* pci; } ;

/* Variables and functions */
 scalar_t__ AZX_DRIVER_SKL ; 
 int /*<<< orphan*/  INTEL_HDA_CGCTL ; 
 int INTEL_HDA_CGCTL_MISCBDCGE ; 
 scalar_t__ IS_BXT (struct pci_dev*) ; 
 struct hdac_bus* azx_bus (struct azx*) ; 
 int /*<<< orphan*/  azx_init_chip (struct azx*,int) ; 
 int /*<<< orphan*/  bxt_reduce_dma_latency (struct azx*) ; 
 int /*<<< orphan*/  intel_init_lctl (struct azx*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hdac_set_codec_wakeup (struct hdac_bus*,int) ; 

__attribute__((used)) static void hda_intel_init_chip(struct azx *chip, bool full_reset)
{
	struct hdac_bus *bus = azx_bus(chip);
	struct pci_dev *pci = chip->pci;
	u32 val;

	snd_hdac_set_codec_wakeup(bus, true);
	if (chip->driver_type == AZX_DRIVER_SKL) {
		pci_read_config_dword(pci, INTEL_HDA_CGCTL, &val);
		val = val & ~INTEL_HDA_CGCTL_MISCBDCGE;
		pci_write_config_dword(pci, INTEL_HDA_CGCTL, val);
	}
	azx_init_chip(chip, full_reset);
	if (chip->driver_type == AZX_DRIVER_SKL) {
		pci_read_config_dword(pci, INTEL_HDA_CGCTL, &val);
		val = val | INTEL_HDA_CGCTL_MISCBDCGE;
		pci_write_config_dword(pci, INTEL_HDA_CGCTL, val);
	}

	snd_hdac_set_codec_wakeup(bus, false);

	/* reduce dma latency to avoid noise */
	if (IS_BXT(pci))
		bxt_reduce_dma_latency(chip);

	if (bus->mlcap != NULL)
		intel_init_lctl(chip);
}