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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int vendor; int device; } ;
struct usb_ftdi {int function; scalar_t__ enumerated; TYPE_1__ platform_data; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OHCI_QUIRK_AMD756 ; 
 int /*<<< orphan*/  OHCI_QUIRK_ZFMICRO ; 
 int PCI_VENDOR_ID_AL ; 
 int PCI_VENDOR_ID_AMD ; 
 int PCI_VENDOR_ID_ATT ; 
 int PCI_VENDOR_ID_COMPAQ ; 
 int PCI_VENDOR_ID_NEC ; 
 int PCI_VENDOR_ID_OPTI ; 
 int ftdi_elan_found_controller (struct usb_ftdi*,int,int /*<<< orphan*/ ) ; 
 int ftdi_elan_read_config (struct usb_ftdi*,int,int /*<<< orphan*/ ,int*) ; 
 int ftdi_elan_setup_controller (struct usb_ftdi*,int) ; 

__attribute__((used)) static int ftdi_elan_setupOHCI(struct usb_ftdi *ftdi)
{
	int UxxxStatus;
	u32 pcidata;
	int reg = 0;
	u8 fn;
	int activePCIfn = 0;
	int max_devices = 0;
	int controllers = 0;
	int unrecognized = 0;
	ftdi->function = 0;
	for (fn = 0; (fn < 4); fn++) {
		u32 pciVID = 0;
		u32 pciPID = 0;
		int devices = 0;
		activePCIfn = fn << 8;
		UxxxStatus = ftdi_elan_read_config(ftdi, activePCIfn | reg, 0,
						   &pcidata);
		if (UxxxStatus)
			return UxxxStatus;
		pciVID = pcidata & 0xFFFF;
		pciPID = (pcidata >> 16) & 0xFFFF;
		if ((pciVID == PCI_VENDOR_ID_OPTI) && (pciPID == 0xc861)) {
			devices = ftdi_elan_found_controller(ftdi, fn, 0);
			controllers += 1;
		} else if ((pciVID == PCI_VENDOR_ID_NEC) && (pciPID == 0x0035))
		{
			devices = ftdi_elan_found_controller(ftdi, fn, 0);
			controllers += 1;
		} else if ((pciVID == PCI_VENDOR_ID_AL) && (pciPID == 0x5237)) {
			devices = ftdi_elan_found_controller(ftdi, fn, 0);
			controllers += 1;
		} else if ((pciVID == PCI_VENDOR_ID_ATT) && (pciPID == 0x5802))
		{
			devices = ftdi_elan_found_controller(ftdi, fn, 0);
			controllers += 1;
		} else if (pciVID == PCI_VENDOR_ID_AMD && pciPID == 0x740c) {
			devices = ftdi_elan_found_controller(ftdi, fn,
							     OHCI_QUIRK_AMD756);
			controllers += 1;
		} else if (pciVID == PCI_VENDOR_ID_COMPAQ && pciPID == 0xa0f8) {
			devices = ftdi_elan_found_controller(ftdi, fn,
							     OHCI_QUIRK_ZFMICRO);
			controllers += 1;
		} else if (0 == pcidata) {
		} else
			unrecognized += 1;
		if (devices > max_devices) {
			max_devices = devices;
			ftdi->function = fn + 1;
			ftdi->platform_data.vendor = pciVID;
			ftdi->platform_data.device = pciPID;
		}
	}
	if (ftdi->function > 0) {
		return ftdi_elan_setup_controller(ftdi,	ftdi->function - 1);
	} else if (controllers > 0) {
		return -ENXIO;
	} else if (unrecognized > 0) {
		return -ENXIO;
	} else {
		ftdi->enumerated = 0;
		return -ENXIO;
	}
}