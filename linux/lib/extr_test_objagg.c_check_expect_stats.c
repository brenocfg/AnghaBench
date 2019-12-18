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
struct objagg {int dummy; } ;
struct expect_stats {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct objagg_stats const*) ; 
 int PTR_ERR (struct objagg_stats const*) ; 
 int __check_expect_stats (struct objagg_stats const*,struct expect_stats const*,char const**) ; 
 struct objagg_stats* objagg_stats_get (struct objagg*) ; 
 int /*<<< orphan*/  objagg_stats_put (struct objagg_stats const*) ; 

__attribute__((used)) static int check_expect_stats(struct objagg *objagg,
			      const struct expect_stats *expect_stats,
			      const char **errmsg)
{
	const struct objagg_stats *stats;
	int err;

	stats = objagg_stats_get(objagg);
	if (IS_ERR(stats)) {
		*errmsg = "objagg_stats_get() failed.";
		return PTR_ERR(stats);
	}
	err = __check_expect_stats(stats, expect_stats, errmsg);
	objagg_stats_put(stats);
	return err;
}