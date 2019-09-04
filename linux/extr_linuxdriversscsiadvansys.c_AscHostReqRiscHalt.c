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
typedef  int uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int /*<<< orphan*/  ASCV_STOP_CODE_B ; 
 int ASC_STOP_HOST_REQ_RISC_HALT ; 
 int ASC_STOP_REQ_RISC_STOP ; 
 scalar_t__ AscIsChipHalted (int /*<<< orphan*/ ) ; 
 int AscReadLramByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscWriteLramByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static bool AscHostReqRiscHalt(PortAddr iop_base)
{
	int count = 0;
	bool sta = false;
	uchar saved_stop_code;

	if (AscIsChipHalted(iop_base))
		return true;
	saved_stop_code = AscReadLramByte(iop_base, ASCV_STOP_CODE_B);
	AscWriteLramByte(iop_base, ASCV_STOP_CODE_B,
			 ASC_STOP_HOST_REQ_RISC_HALT | ASC_STOP_REQ_RISC_STOP);
	do {
		if (AscIsChipHalted(iop_base)) {
			sta = true;
			break;
		}
		mdelay(100);
	} while (count++ < 20);
	AscWriteLramByte(iop_base, ASCV_STOP_CODE_B, saved_stop_code);
	return sta;
}