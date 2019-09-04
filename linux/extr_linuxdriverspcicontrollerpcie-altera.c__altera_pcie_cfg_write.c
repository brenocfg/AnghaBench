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
typedef  int u8 ;
typedef  int u32 ;
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 int DWORD_MASK ; 
 int tlp_cfg_dword_write (struct altera_pcie*,int,unsigned int,int,int,int) ; 

__attribute__((used)) static int _altera_pcie_cfg_write(struct altera_pcie *pcie, u8 busno,
				  unsigned int devfn, int where, int size,
				  u32 value)
{
	u32 data32;
	u32 shift = 8 * (where & 3);
	u8 byte_en;

	switch (size) {
	case 1:
		data32 = (value & 0xff) << shift;
		byte_en = 1 << (where & 3);
		break;
	case 2:
		data32 = (value & 0xffff) << shift;
		byte_en = 3 << (where & 3);
		break;
	default:
		data32 = value;
		byte_en = 0xf;
		break;
	}

	return tlp_cfg_dword_write(pcie, busno, devfn, (where & ~DWORD_MASK),
				   byte_en, data32);
}