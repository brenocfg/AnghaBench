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
typedef  scalar_t__ uint32_t ;
struct cgroup {scalar_t__ hash; int /*<<< orphan*/  id; struct cgroup* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CGROUP ; 
 struct cgroup* cgroup_root ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ simple_hash (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct cgroup *cgroup_find(const char *id) {
    debug(D_CGROUP, "searching for cgroup '%s'", id);

    uint32_t hash = simple_hash(id);

    struct cgroup *cg;
    for(cg = cgroup_root; cg ; cg = cg->next) {
        if(hash == cg->hash && strcmp(id, cg->id) == 0)
            break;
    }

    debug(D_CGROUP, "cgroup '%s' %s in memory", id, (cg)?"found":"not found");
    return cg;
}