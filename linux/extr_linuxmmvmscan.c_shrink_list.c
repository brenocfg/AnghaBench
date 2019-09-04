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
struct scan_control {int dummy; } ;
struct mem_cgroup {int dummy; } ;
struct lruvec {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 scalar_t__ inactive_list_is_low (struct lruvec*,int /*<<< orphan*/ ,struct mem_cgroup*,struct scan_control*,int) ; 
 scalar_t__ is_active_lru (int) ; 
 int /*<<< orphan*/  is_file_lru (int) ; 
 int /*<<< orphan*/  shrink_active_list (unsigned long,struct lruvec*,struct scan_control*,int) ; 
 unsigned long shrink_inactive_list (unsigned long,struct lruvec*,struct scan_control*,int) ; 

__attribute__((used)) static unsigned long shrink_list(enum lru_list lru, unsigned long nr_to_scan,
				 struct lruvec *lruvec, struct mem_cgroup *memcg,
				 struct scan_control *sc)
{
	if (is_active_lru(lru)) {
		if (inactive_list_is_low(lruvec, is_file_lru(lru),
					 memcg, sc, true))
			shrink_active_list(nr_to_scan, lruvec, sc, lru);
		return 0;
	}

	return shrink_inactive_list(nr_to_scan, lruvec, sc, lru);
}