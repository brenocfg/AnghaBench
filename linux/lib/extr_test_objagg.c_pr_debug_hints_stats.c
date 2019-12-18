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
struct objagg_stats {int dummy; } ;
struct objagg_hints {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct objagg_stats const*) ; 
 int /*<<< orphan*/  __pr_debug_stats (struct objagg_stats const*) ; 
 struct objagg_stats* objagg_hints_stats_get (struct objagg_hints*) ; 
 int /*<<< orphan*/  objagg_stats_put (struct objagg_stats const*) ; 

__attribute__((used)) static void pr_debug_hints_stats(struct objagg_hints *objagg_hints)
{
	const struct objagg_stats *stats;

	stats = objagg_hints_stats_get(objagg_hints);
	if (IS_ERR(stats))
		return;
	__pr_debug_stats(stats);
	objagg_stats_put(stats);
}