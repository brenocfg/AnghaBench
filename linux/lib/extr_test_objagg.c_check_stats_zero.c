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
struct objagg_stats {scalar_t__ stats_info_count; } ;
struct objagg {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct objagg_stats const*) ; 
 int PTR_ERR (struct objagg_stats const*) ; 
 struct objagg_stats* objagg_stats_get (struct objagg*) ; 
 int /*<<< orphan*/  objagg_stats_put (struct objagg_stats const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int check_stats_zero(struct objagg *objagg)
{
	const struct objagg_stats *stats;
	int err = 0;

	stats = objagg_stats_get(objagg);
	if (IS_ERR(stats))
		return PTR_ERR(stats);

	if (stats->stats_info_count != 0) {
		pr_err("Stats: Object count is not zero while it should be\n");
		err = -EINVAL;
	}

	objagg_stats_put(stats);
	return err;
}