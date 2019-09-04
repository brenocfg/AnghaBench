#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * chpid; } ;
struct TYPE_4__ {TYPE_1__ pmcw; } ;
struct subchannel {int lpm; TYPE_2__ schib; } ;
struct chp_id {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  chp_id_init (struct chp_id*) ; 
 int /*<<< orphan*/  chp_is_registered (struct chp_id) ; 
 int /*<<< orphan*/  css_schedule_eval_all () ; 

__attribute__((used)) static void
__recover_lost_chpids(struct subchannel *sch, int old_lpm)
{
	int mask, i;
	struct chp_id chpid;

	chp_id_init(&chpid);
	for (i = 0; i<8; i++) {
		mask = 0x80 >> i;
		if (!(sch->lpm & mask))
			continue;
		if (old_lpm & mask)
			continue;
		chpid.id = sch->schib.pmcw.chpid[i];
		if (!chp_is_registered(chpid))
			css_schedule_eval_all();
	}
}