#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpwd {TYPE_1__* devs; scalar_t__ broken; } ;
struct TYPE_2__ {unsigned char intr_mask; int runstatus; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ PLD_IMASK ; 
 unsigned char WD_EXPIRED ; 
 unsigned char WD_FREERUN ; 
 unsigned char WD_RUNNING ; 
 unsigned char WD_SERVICED ; 
 scalar_t__ WD_STATUS ; 
 int WD_STAT_BSTOP ; 
 int WD_STAT_SVCD ; 
 unsigned char WD_STOPPED ; 
 unsigned char WD_S_EXPIRED ; 
 unsigned char WD_S_RUNNING ; 
 unsigned char cpwd_readb (scalar_t__) ; 

__attribute__((used)) static int cpwd_getstatus(struct cpwd *p, int index)
{
	unsigned char stat = cpwd_readb(p->devs[index].regs + WD_STATUS);
	unsigned char intr = cpwd_readb(p->devs[index].regs + PLD_IMASK);
	unsigned char ret  = WD_STOPPED;

	/* determine STOPPED */
	if (!stat)
		return ret;

	/* determine EXPIRED vs FREERUN vs RUNNING */
	else if (WD_S_EXPIRED & stat) {
		ret = WD_EXPIRED;
	} else if (WD_S_RUNNING & stat) {
		if (intr & p->devs[index].intr_mask) {
			ret = WD_FREERUN;
		} else {
			/* Fudge WD_EXPIRED status for defective CP1400--
			 * IF timer is running
			 *	AND brokenstop is set
			 *	AND an interrupt has been serviced
			 * we are WD_EXPIRED.
			 *
			 * IF timer is running
			 *	AND brokenstop is set
			 *	AND no interrupt has been serviced
			 * we are WD_FREERUN.
			 */
			if (p->broken &&
			    (p->devs[index].runstatus & WD_STAT_BSTOP)) {
				if (p->devs[index].runstatus & WD_STAT_SVCD) {
					ret = WD_EXPIRED;
				} else {
					/* we could as well pretend
					 * we are expired */
					ret = WD_FREERUN;
				}
			} else {
				ret = WD_RUNNING;
			}
		}
	}

	/* determine SERVICED */
	if (p->devs[index].runstatus & WD_STAT_SVCD)
		ret |= WD_SERVICED;

	return ret;
}