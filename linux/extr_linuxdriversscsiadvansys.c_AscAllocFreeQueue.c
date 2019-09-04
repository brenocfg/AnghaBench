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
typedef  scalar_t__ ushort ;
typedef  scalar_t__ uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 scalar_t__ ASC_QLINK_END ; 
 scalar_t__ ASC_QNO_TO_QADDR (scalar_t__) ; 
 scalar_t__ ASC_SCSIQ_B_FWD ; 
 scalar_t__ ASC_SCSIQ_B_STATUS ; 
 scalar_t__ AscReadLramByte (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ QS_READY ; 

__attribute__((used)) static uchar AscAllocFreeQueue(PortAddr iop_base, uchar free_q_head)
{
	ushort q_addr;
	uchar next_qp;
	uchar q_status;

	q_addr = ASC_QNO_TO_QADDR(free_q_head);
	q_status = (uchar)AscReadLramByte(iop_base,
					  (ushort)(q_addr +
						   ASC_SCSIQ_B_STATUS));
	next_qp = AscReadLramByte(iop_base, (ushort)(q_addr + ASC_SCSIQ_B_FWD));
	if (((q_status & QS_READY) == 0) && (next_qp != ASC_QLINK_END))
		return next_qp;
	return ASC_QLINK_END;
}