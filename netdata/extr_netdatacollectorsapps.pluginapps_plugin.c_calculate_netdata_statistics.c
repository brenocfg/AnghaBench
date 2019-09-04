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
struct target {scalar_t__ uid; scalar_t__ gid; int /*<<< orphan*/  name; } ;
struct pid_stat {scalar_t__ uid; scalar_t__ gid; struct target* group_target; int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; struct target* user_target; struct target* target; struct pid_stat* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  aggregate_pid_fds_on_targets (struct pid_stat*) ; 
 int /*<<< orphan*/  aggregate_pid_on_target (struct target*,struct pid_stat*,struct target*) ; 
 int /*<<< orphan*/  apply_apps_groups_targets_inheritance () ; 
 int /*<<< orphan*/  apps_groups_root_target ; 
 int /*<<< orphan*/  apps_groups_targets_count ; 
 int /*<<< orphan*/  cleanup_exited_pids () ; 
 scalar_t__ debug_enabled ; 
 int /*<<< orphan*/  debug_log (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ enable_file_charts ; 
 struct target* get_groups_target (scalar_t__) ; 
 struct target* get_users_target (scalar_t__) ; 
 int /*<<< orphan*/  groups_root_target ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct pid_stat* root_of_pids ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  users_root_target ; 
 int /*<<< orphan*/  zero_all_targets (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void calculate_netdata_statistics(void) {

    apply_apps_groups_targets_inheritance();

    zero_all_targets(users_root_target);
    zero_all_targets(groups_root_target);
    apps_groups_targets_count = zero_all_targets(apps_groups_root_target);

    // this has to be done, before the cleanup
    struct pid_stat *p = NULL;
    struct target *w = NULL, *o = NULL;

    // concentrate everything on the targets
    for(p = root_of_pids; p ; p = p->next) {

        // --------------------------------------------------------------------
        // apps_groups target

        aggregate_pid_on_target(p->target, p, NULL);


        // --------------------------------------------------------------------
        // user target

        o = p->user_target;
        if(likely(p->user_target && p->user_target->uid == p->uid))
            w = p->user_target;
        else {
            if(unlikely(debug_enabled && p->user_target))
                debug_log("pid %d (%s) switched user from %u (%s) to %u.", p->pid, p->comm, p->user_target->uid, p->user_target->name, p->uid);

            w = p->user_target = get_users_target(p->uid);
        }

        aggregate_pid_on_target(w, p, o);


        // --------------------------------------------------------------------
        // user group target

        o = p->group_target;
        if(likely(p->group_target && p->group_target->gid == p->gid))
            w = p->group_target;
        else {
            if(unlikely(debug_enabled && p->group_target))
                debug_log("pid %d (%s) switched group from %u (%s) to %u.", p->pid, p->comm, p->group_target->gid, p->group_target->name, p->gid);

            w = p->group_target = get_groups_target(p->gid);
        }

        aggregate_pid_on_target(w, p, o);


        // --------------------------------------------------------------------
        // aggregate all file descriptors

        if(enable_file_charts)
            aggregate_pid_fds_on_targets(p);
    }

    cleanup_exited_pids();
}