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
struct timex {scalar_t__ status; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_STATUS ; 
 int adjtimex (struct timex*) ; 

int clear_time_state(void)
{
	struct timex tx;
	int ret;

	tx.modes = ADJ_STATUS;
	tx.status = 0;
	ret = adjtimex(&tx);
	return ret;
}