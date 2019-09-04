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
struct TYPE_3__ {int /*<<< orphan*/ * tm_next; int /*<<< orphan*/  tm_active; } ;
struct TYPE_4__ {TYPE_1__ st_fast; int /*<<< orphan*/ * st_queue; } ;
struct s_smc {TYPE_2__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  hwt_init (struct s_smc*) ; 

void smt_timer_init(struct s_smc *smc)
{
	smc->t.st_queue = NULL;
	smc->t.st_fast.tm_active = FALSE ;
	smc->t.st_fast.tm_next = NULL;
	hwt_init(smc) ;
}