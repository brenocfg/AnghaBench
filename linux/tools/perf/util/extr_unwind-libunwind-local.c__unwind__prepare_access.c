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
struct map_groups {int /*<<< orphan*/  addr_space; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  UNW_CACHE_GLOBAL ; 
 int /*<<< orphan*/  accessors ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  unw_create_addr_space (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unw_set_caching_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _unwind__prepare_access(struct map_groups *mg)
{
	mg->addr_space = unw_create_addr_space(&accessors, 0);
	if (!mg->addr_space) {
		pr_err("unwind: Can't create unwind address space.\n");
		return -ENOMEM;
	}

	unw_set_caching_policy(mg->addr_space, UNW_CACHE_GLOBAL);
	return 0;
}