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
typedef  int PortAddr ;

/* Variables and functions */
 int ASC_CHIP_MIN_VER_EISA ; 
 scalar_t__ ASC_EISA_REV_IOP_MASK ; 
 scalar_t__ ASC_GET_EISA_SLOT (int) ; 
 unsigned short ASC_IS_EISA ; 
 unsigned char AscGetChipVerNo (int) ; 
 unsigned char inp (int) ; 

__attribute__((used)) static unsigned char AscGetChipVersion(PortAddr iop_base,
				       unsigned short bus_type)
{
	if (bus_type & ASC_IS_EISA) {
		PortAddr eisa_iop;
		unsigned char revision;
		eisa_iop = (PortAddr) ASC_GET_EISA_SLOT(iop_base) |
		    (PortAddr) ASC_EISA_REV_IOP_MASK;
		revision = inp(eisa_iop);
		return ASC_CHIP_MIN_VER_EISA - 1 + revision;
	}
	return AscGetChipVerNo(iop_base);
}