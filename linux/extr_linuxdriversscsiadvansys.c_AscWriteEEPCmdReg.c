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
typedef  unsigned char uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int ASC_EEP_MAX_RETRY ; 
 unsigned char AscGetChipEEPCmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipEEPCmd (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int AscWriteEEPCmdReg(PortAddr iop_base, uchar cmd_reg)
{
	int retry;

	for (retry = 0; retry < ASC_EEP_MAX_RETRY; retry++) {
		unsigned char read_back;
		AscSetChipEEPCmd(iop_base, cmd_reg);
		mdelay(1);
		read_back = AscGetChipEEPCmd(iop_base);
		if (read_back == cmd_reg)
			return 1;
	}
	return 0;
}