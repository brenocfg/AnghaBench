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
struct tc_netem_reorder {int /*<<< orphan*/  correlation; int /*<<< orphan*/  probability; } ;
struct nlattr {int dummy; } ;
struct netem_sched_data {int /*<<< orphan*/  reorder_cor; int /*<<< orphan*/  reorder; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_crandom (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tc_netem_reorder* nla_data (struct nlattr const*) ; 

__attribute__((used)) static void get_reorder(struct netem_sched_data *q, const struct nlattr *attr)
{
	const struct tc_netem_reorder *r = nla_data(attr);

	q->reorder = r->probability;
	init_crandom(&q->reorder_cor, r->correlation);
}