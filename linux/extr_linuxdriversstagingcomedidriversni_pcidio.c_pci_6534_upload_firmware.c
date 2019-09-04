#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nidio96_private {TYPE_2__* mite; } ;
struct comedi_device {struct nidio96_private* private; } ;
struct TYPE_4__ {TYPE_1__* pcidev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  FW_PCI_6534_MAIN 130 
#define  FW_PCI_6534_SCARAB_DI 129 
#define  FW_PCI_6534_SCARAB_DO 128 
 int comedi_load_firmware (struct comedi_device*,int /*<<< orphan*/ *,char const* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_6534_init_main_fpga (struct comedi_device*) ; 
 int /*<<< orphan*/  pci_6534_load_fpga ; 
 int pci_6534_reset_fpgas (struct comedi_device*) ; 

__attribute__((used)) static int pci_6534_upload_firmware(struct comedi_device *dev)
{
	struct nidio96_private *devpriv = dev->private;
	static const char *const fw_file[3] = {
		FW_PCI_6534_SCARAB_DI,	/* loaded into scarab A for DI */
		FW_PCI_6534_SCARAB_DO,	/* loaded into scarab B for DO */
		FW_PCI_6534_MAIN,	/* loaded into main FPGA */
	};
	int ret;
	int n;

	ret = pci_6534_reset_fpgas(dev);
	if (ret < 0)
		return ret;
	/* load main FPGA first, then the two scarabs */
	for (n = 2; n >= 0; n--) {
		ret = comedi_load_firmware(dev, &devpriv->mite->pcidev->dev,
					   fw_file[n],
					   pci_6534_load_fpga, n);
		if (ret == 0 && n == 2)
			pci_6534_init_main_fpga(dev);
		if (ret < 0)
			break;
	}
	return ret;
}