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
struct cgroup {int enabled; int options; scalar_t__ hash_chart; struct cgroup* next; int /*<<< orphan*/  id; int /*<<< orphan*/  chart_id; scalar_t__ available; } ;

/* Variables and functions */
 int CGROUP_OPTIONS_DISABLED_DUPLICATE ; 
 int /*<<< orphan*/  D_CGROUP ; 
 int /*<<< orphan*/  cgroup_free (struct cgroup*) ; 
 struct cgroup* cgroup_root ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cleanup_all_cgroups() {
    struct cgroup *cg = cgroup_root, *last = NULL;

    for(; cg ;) {
        if(!cg->available) {
            // enable the first duplicate cgroup
            {
                struct cgroup *t;
                for(t = cgroup_root; t ; t = t->next) {
                    if(t != cg && t->available && !t->enabled && t->options & CGROUP_OPTIONS_DISABLED_DUPLICATE && t->hash_chart == cg->hash_chart && !strcmp(t->chart_id, cg->chart_id)) {
                        debug(D_CGROUP, "Enabling duplicate of cgroup '%s' with id '%s', because the original with id '%s' stopped.", t->chart_id, t->id, cg->id);
                        t->enabled = 1;
                        t->options &= ~CGROUP_OPTIONS_DISABLED_DUPLICATE;
                        break;
                    }
                }
            }

            if(!last)
                cgroup_root = cg->next;
            else
                last->next = cg->next;

            cgroup_free(cg);

            if(!last)
                cg = cgroup_root;
            else
                cg = last->next;
        }
        else {
            last = cg;
            cg = cg->next;
        }
    }
}