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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 unsigned char PCI_VPD_LRDT ; 
 scalar_t__ PCI_VPD_LRDT_TAG_SIZE ; 
 unsigned char PCI_VPD_LTIN_ID_STRING ; 
 unsigned char PCI_VPD_LTIN_RO_DATA ; 
 unsigned char PCI_VPD_LTIN_RW_DATA ; 
 scalar_t__ PCI_VPD_SRDT_TAG_SIZE ; 
 unsigned char PCI_VPD_STIN_END ; 
 int pci_read_vpd (struct pci_dev*,size_t,int,unsigned char*) ; 
 scalar_t__ pci_vpd_lrdt_size (unsigned char*) ; 
 unsigned char pci_vpd_lrdt_tag (unsigned char*) ; 
 scalar_t__ pci_vpd_srdt_size (unsigned char*) ; 
 unsigned char pci_vpd_srdt_tag (unsigned char*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*,...) ; 

__attribute__((used)) static size_t pci_vpd_size(struct pci_dev *dev, size_t old_size)
{
	size_t off = 0;
	unsigned char header[1+2];	/* 1 byte tag, 2 bytes length */

	while (off < old_size &&
	       pci_read_vpd(dev, off, 1, header) == 1) {
		unsigned char tag;

		if (header[0] & PCI_VPD_LRDT) {
			/* Large Resource Data Type Tag */
			tag = pci_vpd_lrdt_tag(header);
			/* Only read length from known tag items */
			if ((tag == PCI_VPD_LTIN_ID_STRING) ||
			    (tag == PCI_VPD_LTIN_RO_DATA) ||
			    (tag == PCI_VPD_LTIN_RW_DATA)) {
				if (pci_read_vpd(dev, off+1, 2,
						 &header[1]) != 2) {
					pci_warn(dev, "invalid large VPD tag %02x size at offset %zu",
						 tag, off + 1);
					return 0;
				}
				off += PCI_VPD_LRDT_TAG_SIZE +
					pci_vpd_lrdt_size(header);
			}
		} else {
			/* Short Resource Data Type Tag */
			off += PCI_VPD_SRDT_TAG_SIZE +
				pci_vpd_srdt_size(header);
			tag = pci_vpd_srdt_tag(header);
		}

		if (tag == PCI_VPD_STIN_END)	/* End tag descriptor */
			return off;

		if ((tag != PCI_VPD_LTIN_ID_STRING) &&
		    (tag != PCI_VPD_LTIN_RO_DATA) &&
		    (tag != PCI_VPD_LTIN_RW_DATA)) {
			pci_warn(dev, "invalid %s VPD tag %02x at offset %zu",
				 (header[0] & PCI_VPD_LRDT) ? "large" : "short",
				 tag, off);
			return 0;
		}
	}
	return 0;
}