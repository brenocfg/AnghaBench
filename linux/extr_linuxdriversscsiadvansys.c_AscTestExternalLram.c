#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort ;
struct TYPE_3__ {int /*<<< orphan*/  iop_base; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_1__ ASC_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_QNO_TO_QADDR (int) ; 
 int AscGetChipLramData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscReadLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipLramAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipLramData (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscWriteLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int AscTestExternalLram(ASC_DVC_VAR *asc_dvc)
{
	PortAddr iop_base;
	ushort q_addr;
	ushort saved_word;
	int sta;

	iop_base = asc_dvc->iop_base;
	sta = 0;
	q_addr = ASC_QNO_TO_QADDR(241);
	saved_word = AscReadLramWord(iop_base, q_addr);
	AscSetChipLramAddr(iop_base, q_addr);
	AscSetChipLramData(iop_base, 0x55AA);
	mdelay(10);
	AscSetChipLramAddr(iop_base, q_addr);
	if (AscGetChipLramData(iop_base) == 0x55AA) {
		sta = 1;
		AscWriteLramWord(iop_base, q_addr, saved_word);
	}
	return (sta);
}