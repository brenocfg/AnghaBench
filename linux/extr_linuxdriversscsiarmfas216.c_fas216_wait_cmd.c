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
typedef  int /*<<< orphan*/  FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  REG_STAT ; 
 int STAT_INT ; 
 int STAT_PARITYERROR ; 
 int /*<<< orphan*/  fas216_cmd (int /*<<< orphan*/ *,int) ; 
 int fas216_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int fas216_wait_cmd(FAS216_Info *info, int cmd)
{
	int tout;
	int stat;

	fas216_cmd(info, cmd);

	for (tout = 1000; tout; tout -= 1) {
		stat = fas216_readb(info, REG_STAT);
		if (stat & (STAT_INT|STAT_PARITYERROR))
			break;
		udelay(1);
	}

	return stat;
}