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
struct cgroup {scalar_t__ available; struct cgroup* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CGROUP ; 
 struct cgroup* cgroup_root ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void mark_all_cgroups_as_not_available() {
    debug(D_CGROUP, "marking all cgroups as not available");

    struct cgroup *cg;

    // mark all as not available
    for(cg = cgroup_root; cg ; cg = cg->next) {
        cg->available = 0;
    }
}