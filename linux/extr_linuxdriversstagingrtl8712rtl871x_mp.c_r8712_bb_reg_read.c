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
typedef  int u16 ;
struct _adapter {int dummy; } ;
struct IOCMD_STRUCT {int value; int /*<<< orphan*/  index; int /*<<< orphan*/  cmdclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCMD_BB_READ_IDX ; 
 int /*<<< orphan*/  IOCMD_CLASS_BB_RF ; 
 int fw_iocmd_read (struct _adapter*,struct IOCMD_STRUCT) ; 

u32 r8712_bb_reg_read(struct _adapter *pAdapter, u16 offset)
{
	u8 shift = offset & 0x0003;	/* 4 byte access */
	u16 bb_addr = offset & 0x0FFC;	/* 4 byte access */
	u32 bb_val = 0;
	struct IOCMD_STRUCT iocmd;

	iocmd.cmdclass	= IOCMD_CLASS_BB_RF;
	iocmd.value	= bb_addr;
	iocmd.index	= IOCMD_BB_READ_IDX;
	bb_val = fw_iocmd_read(pAdapter, iocmd);
	if (shift != 0) {
		u32 bb_val2 = 0;

		bb_val >>= (shift * 8);
		iocmd.value += 4;
		bb_val2 = fw_iocmd_read(pAdapter, iocmd);
		bb_val2 <<= ((4 - shift) * 8);
		bb_val |= bb_val2;
	}
	return bb_val;
}