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
typedef  int u64 ;
struct ui_progress {int curr; scalar_t__ next; int step; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update ) (struct ui_progress*) ;} ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  stub1 (struct ui_progress*) ; 
 TYPE_1__* ui_progress__ops ; 

void ui_progress__update(struct ui_progress *p, u64 adv)
{
	u64 last = p->curr;

	p->curr += adv;

	if (p->curr >= p->next) {
		u64 nr = DIV_ROUND_UP(p->curr - last, p->step);

		p->next += nr * p->step;
		ui_progress__ops->update(p);
	}
}