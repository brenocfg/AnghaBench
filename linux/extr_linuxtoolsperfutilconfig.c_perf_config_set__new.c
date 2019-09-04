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
struct perf_config_set {int /*<<< orphan*/  sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_config_set__init (struct perf_config_set*) ; 
 struct perf_config_set* zalloc (int) ; 

struct perf_config_set *perf_config_set__new(void)
{
	struct perf_config_set *set = zalloc(sizeof(*set));

	if (set) {
		INIT_LIST_HEAD(&set->sections);
		perf_config_set__init(set);
	}

	return set;
}