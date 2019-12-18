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
typedef  int u32 ;
struct TYPE_2__ {unsigned int wp; unsigned int rp; scalar_t__ cmds; int /*<<< orphan*/ * buf; } ;
struct lola {int res; int res_ex; TYPE_1__ rirb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR0 ; 
 unsigned int LOLA_CORB_ENTRIES ; 
 int LOLA_RIRB_EX_UNSOL_EV ; 
 int /*<<< orphan*/  RIRBWP ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lola_queue_unsol_event (struct lola*,int,int) ; 
 unsigned int lola_readw (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void lola_update_rirb(struct lola *chip)
{
	unsigned int rp, wp;
	u32 res, res_ex;

	wp = lola_readw(chip, BAR0, RIRBWP);
	if (wp == chip->rirb.wp)
		return;
	chip->rirb.wp = wp;

	while (chip->rirb.rp != wp) {
		chip->rirb.rp++;
		chip->rirb.rp %= LOLA_CORB_ENTRIES;

		rp = chip->rirb.rp << 1; /* an RIRB entry is 8-bytes */
		res_ex = le32_to_cpu(chip->rirb.buf[rp + 1]);
		res = le32_to_cpu(chip->rirb.buf[rp]);
		if (res_ex & LOLA_RIRB_EX_UNSOL_EV)
			lola_queue_unsol_event(chip, res, res_ex);
		else if (chip->rirb.cmds) {
			chip->res = res;
			chip->res_ex = res_ex;
			smp_wmb();
			chip->rirb.cmds--;
		}
	}
}