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
struct pci_dev {int dummy; } ;
struct hdac_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZX_CGCTL_ADSPDCGE ; 
 int /*<<< orphan*/  AZX_PCIREG_CGCTL ; 
 int /*<<< orphan*/  AZX_PCIREG_PGCTL ; 
 int /*<<< orphan*/  AZX_PGCTL_ADSPPGD ; 
 int /*<<< orphan*/  AZX_REG_VS_EM2_L1SEN ; 
 int /*<<< orphan*/  VS_EM2 ; 
 struct hdac_bus* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  snd_hdac_chip_updatel (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  update_pci_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_clock_power_gating(struct device *dev, bool enable)
{
	struct pci_dev *pci = to_pci_dev(dev);
	struct hdac_bus *bus = pci_get_drvdata(pci);
	u32 val;

	/* Update PDCGE bit of CGCTL register */
	val = enable ? AZX_CGCTL_ADSPDCGE : 0;
	update_pci_dword(pci, AZX_PCIREG_CGCTL, AZX_CGCTL_ADSPDCGE, val);

	/* Update L1SEN bit of EM2 register */
	val = enable ? AZX_REG_VS_EM2_L1SEN : 0;
	snd_hdac_chip_updatel(bus, VS_EM2, AZX_REG_VS_EM2_L1SEN, val);

	/* Update ADSPPGD bit of PGCTL register */
	val = enable ? 0 : AZX_PGCTL_ADSPPGD;
	update_pci_dword(pci, AZX_PCIREG_PGCTL, AZX_PGCTL_ADSPPGD, val);
}