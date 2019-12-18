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
struct target {int target_fds_size; struct pid_on_target* root_pid; scalar_t__ uptime_max; scalar_t__ uptime_sum; scalar_t__ uptime_min; scalar_t__ collected_starttime; scalar_t__ openother; scalar_t__ openeventpolls; scalar_t__ opensignalfds; scalar_t__ opentimerfds; scalar_t__ openeventfds; scalar_t__ openinotifies; scalar_t__ opensockets; scalar_t__ openpipes; scalar_t__ openfiles; scalar_t__ target_fds; scalar_t__ io_storage_bytes_written; scalar_t__ io_storage_bytes_read; scalar_t__ io_logical_bytes_written; scalar_t__ io_logical_bytes_read; scalar_t__ status_vmswap; scalar_t__ status_rssshmem; scalar_t__ status_rssfile; scalar_t__ status_vmshared; scalar_t__ status_vmrss; scalar_t__ status_vmsize; scalar_t__ processes; scalar_t__ num_threads; scalar_t__ cgtime; scalar_t__ cstime; scalar_t__ cutime; scalar_t__ cmajflt; scalar_t__ cminflt; scalar_t__ gtime; scalar_t__ stime; scalar_t__ utime; scalar_t__ majflt; scalar_t__ minflt; struct target* next; } ;
struct pid_on_target {struct pid_on_target* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pid_on_target*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (struct pid_on_target*) ; 

__attribute__((used)) static size_t zero_all_targets(struct target *root) {
    struct target *w;
    size_t count = 0;

    for (w = root; w ; w = w->next) {
        count++;

        w->minflt = 0;
        w->majflt = 0;
        w->utime = 0;
        w->stime = 0;
        w->gtime = 0;
        w->cminflt = 0;
        w->cmajflt = 0;
        w->cutime = 0;
        w->cstime = 0;
        w->cgtime = 0;
        w->num_threads = 0;
        // w->rss = 0;
        w->processes = 0;

        w->status_vmsize = 0;
        w->status_vmrss = 0;
        w->status_vmshared = 0;
        w->status_rssfile = 0;
        w->status_rssshmem = 0;
        w->status_vmswap = 0;

        w->io_logical_bytes_read = 0;
        w->io_logical_bytes_written = 0;
        // w->io_read_calls = 0;
        // w->io_write_calls = 0;
        w->io_storage_bytes_read = 0;
        w->io_storage_bytes_written = 0;
        // w->io_cancelled_write_bytes = 0;

        // zero file counters
        if(w->target_fds) {
            memset(w->target_fds, 0, sizeof(int) * w->target_fds_size);
            w->openfiles = 0;
            w->openpipes = 0;
            w->opensockets = 0;
            w->openinotifies = 0;
            w->openeventfds = 0;
            w->opentimerfds = 0;
            w->opensignalfds = 0;
            w->openeventpolls = 0;
            w->openother = 0;
        }

        w->collected_starttime = 0;
        w->uptime_min = 0;
        w->uptime_sum = 0;
        w->uptime_max = 0;

        if(unlikely(w->root_pid)) {
            struct pid_on_target *pid_on_target_to_free, *pid_on_target = w->root_pid;

            while(pid_on_target) {
                pid_on_target_to_free = pid_on_target;
                pid_on_target = pid_on_target->next;
                free(pid_on_target_to_free);
            }

            w->root_pid = NULL;
        }
    }

    return count;
}