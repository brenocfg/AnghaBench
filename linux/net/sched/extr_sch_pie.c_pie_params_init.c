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
struct pie_params {int alpha; int beta; int limit; int ecn; int bytemode; int /*<<< orphan*/  target; int /*<<< orphan*/  tupdate; } ;

/* Variables and functions */
 int NSEC_PER_MSEC ; 
 int /*<<< orphan*/  PSCHED_NS2TICKS (int) ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static void pie_params_init(struct pie_params *params)
{
	params->alpha = 2;
	params->beta = 20;
	params->tupdate = usecs_to_jiffies(15 * USEC_PER_MSEC);	/* 15 ms */
	params->limit = 1000;	/* default of 1000 packets */
	params->target = PSCHED_NS2TICKS(15 * NSEC_PER_MSEC);	/* 15 ms */
	params->ecn = false;
	params->bytemode = false;
}