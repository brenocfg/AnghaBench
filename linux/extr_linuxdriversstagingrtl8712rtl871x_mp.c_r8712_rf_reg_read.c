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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct _adapter {int dummy; } ;
struct IOCMD_STRUCT {int value; int /*<<< orphan*/  index; int /*<<< orphan*/  cmdclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCMD_CLASS_BB_RF ; 
 int /*<<< orphan*/  IOCMD_RF_READ_IDX ; 
 int /*<<< orphan*/  fw_iocmd_read (struct _adapter*,struct IOCMD_STRUCT) ; 

u32 r8712_rf_reg_read(struct _adapter *pAdapter, u8 path, u8 offset)
{
	u16 rf_addr = (path << 8) | offset;
	struct IOCMD_STRUCT iocmd;

	iocmd.cmdclass	= IOCMD_CLASS_BB_RF;
	iocmd.value	= rf_addr;
	iocmd.index	= IOCMD_RF_READ_IDX;
	return fw_iocmd_read(pAdapter, iocmd);
}