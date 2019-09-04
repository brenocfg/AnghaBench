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
struct dql {unsigned int slack_hold_time; scalar_t__ min_limit; int /*<<< orphan*/  max_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQL_MAX_LIMIT ; 
 int /*<<< orphan*/  dql_reset (struct dql*) ; 

void dql_init(struct dql *dql, unsigned int hold_time)
{
	dql->max_limit = DQL_MAX_LIMIT;
	dql->min_limit = 0;
	dql->slack_hold_time = hold_time;
	dql_reset(dql);
}