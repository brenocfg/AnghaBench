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
struct objagg_stats {int stats_info_count; TYPE_2__* stats_info; } ;
struct objagg {int dummy; } ;
struct TYPE_3__ {int user_count; int delta_user_count; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct objagg_stats const*) ; 
 int NUM_KEYS ; 
 int PTR_ERR (struct objagg_stats const*) ; 
 struct objagg_stats* objagg_stats_get (struct objagg*) ; 
 int /*<<< orphan*/  objagg_stats_put (struct objagg_stats const*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int check_stats_nodelta(struct objagg *objagg)
{
	const struct objagg_stats *stats;
	int i;
	int err;

	stats = objagg_stats_get(objagg);
	if (IS_ERR(stats))
		return PTR_ERR(stats);

	if (stats->stats_info_count != NUM_KEYS) {
		pr_err("Stats: Unexpected object count (%u expected, %u returned)\n",
		       NUM_KEYS, stats->stats_info_count);
		err = -EINVAL;
		goto stats_put;
	}

	for (i = 0; i < stats->stats_info_count; i++) {
		if (stats->stats_info[i].stats.user_count != 2) {
			pr_err("Stats: incorrect user count\n");
			err = -EINVAL;
			goto stats_put;
		}
		if (stats->stats_info[i].stats.delta_user_count != 2) {
			pr_err("Stats: incorrect delta user count\n");
			err = -EINVAL;
			goto stats_put;
		}
	}
	err = 0;

stats_put:
	objagg_stats_put(stats);
	return err;
}