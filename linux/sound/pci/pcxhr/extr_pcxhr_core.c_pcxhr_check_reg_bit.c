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
struct pcxhr_mgr {TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 unsigned char PCXHR_INPB (struct pcxhr_mgr*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,unsigned char,unsigned char) ; 
 int jiffies ; 
 scalar_t__ time_after_eq (unsigned long,int) ; 

__attribute__((used)) static int pcxhr_check_reg_bit(struct pcxhr_mgr *mgr, unsigned int reg,
			       unsigned char mask, unsigned char bit, int time,
			       unsigned char* read)
{
	int i = 0;
	unsigned long end_time = jiffies + (time * HZ + 999) / 1000;
	do {
		*read = PCXHR_INPB(mgr, reg);
		if ((*read & mask) == bit) {
			if (i > 100)
				dev_dbg(&mgr->pci->dev,
					"ATTENTION! check_reg(%x) loopcount=%d\n",
					    reg, i);
			return 0;
		}
		i++;
	} while (time_after_eq(end_time, jiffies));
	dev_err(&mgr->pci->dev,
		   "pcxhr_check_reg_bit: timeout, reg=%x, mask=0x%x, val=%x\n",
		   reg, mask, *read);
	return -EIO;
}