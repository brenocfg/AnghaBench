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
struct objagg_stats {int stats_info_count; int /*<<< orphan*/ * stats_info; } ;
struct expect_stats {int /*<<< orphan*/ * info; } ;

/* Variables and functions */
 int EINVAL ; 
 int check_expect_stats_key_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int check_expect_stats_nums (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_expect_stats_neigh(const struct objagg_stats *stats,
				    const struct expect_stats *expect_stats,
				    int pos)
{
	int i;
	int err;

	for (i = pos - 1; i >= 0; i--) {
		err = check_expect_stats_nums(&stats->stats_info[i],
					      &expect_stats->info[pos], NULL);
		if (err)
			break;
		err = check_expect_stats_key_id(&stats->stats_info[i],
						&expect_stats->info[pos], NULL);
		if (!err)
			return 0;
	}
	for (i = pos + 1; i < stats->stats_info_count; i++) {
		err = check_expect_stats_nums(&stats->stats_info[i],
					      &expect_stats->info[pos], NULL);
		if (err)
			break;
		err = check_expect_stats_key_id(&stats->stats_info[i],
						&expect_stats->info[pos], NULL);
		if (!err)
			return 0;
	}
	return -EINVAL;
}