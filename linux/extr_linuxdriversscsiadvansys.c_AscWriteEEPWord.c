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
typedef  int uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 scalar_t__ ASC_EEP_CMD_WRITE ; 
 int ASC_EEP_CMD_WRITE_ABLE ; 
 int ASC_EEP_CMD_WRITE_DISABLE ; 
 scalar_t__ AscReadEEPWord (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscWaitEEPRead () ; 
 int /*<<< orphan*/  AscWaitEEPWrite () ; 
 int /*<<< orphan*/  AscWriteEEPCmdReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscWriteEEPDataReg (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ushort AscWriteEEPWord(PortAddr iop_base, uchar addr, ushort word_val)
{
	ushort read_wval;

	read_wval = AscReadEEPWord(iop_base, addr);
	if (read_wval != word_val) {
		AscWriteEEPCmdReg(iop_base, ASC_EEP_CMD_WRITE_ABLE);
		AscWaitEEPRead();
		AscWriteEEPDataReg(iop_base, word_val);
		AscWaitEEPRead();
		AscWriteEEPCmdReg(iop_base,
				  (uchar)((uchar)ASC_EEP_CMD_WRITE | addr));
		AscWaitEEPWrite();
		AscWriteEEPCmdReg(iop_base, ASC_EEP_CMD_WRITE_DISABLE);
		AscWaitEEPRead();
		return (AscReadEEPWord(iop_base, addr));
	}
	return (read_wval);
}