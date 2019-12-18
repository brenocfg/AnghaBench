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

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*,int,unsigned char) ; 
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,int) ; 
 unsigned char PCI_ANY_ID ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 int class ; 
 int class_mask ; 
 unsigned char device ; 
 int /*<<< orphan*/  pci_device_id ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 unsigned char subdevice ; 
 unsigned char subvendor ; 
 unsigned char vendor ; 
 int /*<<< orphan*/  warn (char*,char const*,int) ; 

__attribute__((used)) static int do_pci_entry(const char *filename,
			void *symval, char *alias)
{
	/* Class field can be divided into these three. */
	unsigned char baseclass, subclass, interface,
		baseclass_mask, subclass_mask, interface_mask;

	DEF_FIELD(symval, pci_device_id, vendor);
	DEF_FIELD(symval, pci_device_id, device);
	DEF_FIELD(symval, pci_device_id, subvendor);
	DEF_FIELD(symval, pci_device_id, subdevice);
	DEF_FIELD(symval, pci_device_id, class);
	DEF_FIELD(symval, pci_device_id, class_mask);

	strcpy(alias, "pci:");
	ADD(alias, "v", vendor != PCI_ANY_ID, vendor);
	ADD(alias, "d", device != PCI_ANY_ID, device);
	ADD(alias, "sv", subvendor != PCI_ANY_ID, subvendor);
	ADD(alias, "sd", subdevice != PCI_ANY_ID, subdevice);

	baseclass = (class) >> 16;
	baseclass_mask = (class_mask) >> 16;
	subclass = (class) >> 8;
	subclass_mask = (class_mask) >> 8;
	interface = class;
	interface_mask = class_mask;

	if ((baseclass_mask != 0 && baseclass_mask != 0xFF)
	    || (subclass_mask != 0 && subclass_mask != 0xFF)
	    || (interface_mask != 0 && interface_mask != 0xFF)) {
		warn("Can't handle masks in %s:%04X\n",
		     filename, class_mask);
		return 0;
	}

	ADD(alias, "bc", baseclass_mask == 0xFF, baseclass);
	ADD(alias, "sc", subclass_mask == 0xFF, subclass);
	ADD(alias, "i", interface_mask == 0xFF, interface);
	add_wildcard(alias);
	return 1;
}