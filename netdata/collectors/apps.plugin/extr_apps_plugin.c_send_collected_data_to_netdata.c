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
typedef  int /*<<< orphan*/  usec_t ;
struct target {unsigned long long processes; int utime; int stime; int gtime; int cutime; int cstime; int cgtime; unsigned long long num_threads; scalar_t__ starttime; unsigned long long uptime_min; unsigned long long uptime_sum; unsigned long long uptime_max; scalar_t__ status_vmrss; scalar_t__ status_vmshared; unsigned long long status_vmsize; unsigned long long status_vmswap; int minflt; int cminflt; int majflt; int cmajflt; unsigned long long io_logical_bytes_read; unsigned long long io_logical_bytes_written; unsigned long long io_storage_bytes_read; unsigned long long io_storage_bytes_written; unsigned long long openfiles; unsigned long long opensockets; unsigned long long openpipes; int /*<<< orphan*/  name; scalar_t__ exposed; struct target* next; } ;
typedef  unsigned long long kernel_uint_t ;

/* Variables and functions */
 int cgtime_fix_ratio ; 
 int cmajflt_fix_ratio ; 
 int cminflt_fix_ratio ; 
 int cstime_fix_ratio ; 
 int cutime_fix_ratio ; 
 scalar_t__ enable_file_charts ; 
 scalar_t__ global_uptime ; 
 int gtime_fix_ratio ; 
 scalar_t__ include_exited_childs ; 
 int majflt_fix_ratio ; 
 int minflt_fix_ratio ; 
 int /*<<< orphan*/  send_BEGIN (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_END () ; 
 int /*<<< orphan*/  send_SET (int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ show_guest_time ; 
 int stime_fix_ratio ; 
 scalar_t__ unlikely (int) ; 
 int utime_fix_ratio ; 

__attribute__((used)) static void send_collected_data_to_netdata(struct target *root, const char *type, usec_t dt) {
    struct target *w;

    send_BEGIN(type, "cpu", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, (kernel_uint_t)(w->utime * utime_fix_ratio) + (kernel_uint_t)(w->stime * stime_fix_ratio) + (kernel_uint_t)(w->gtime * gtime_fix_ratio) + (include_exited_childs?((kernel_uint_t)(w->cutime * cutime_fix_ratio) + (kernel_uint_t)(w->cstime * cstime_fix_ratio) + (kernel_uint_t)(w->cgtime * cgtime_fix_ratio)):0ULL));
    }
    send_END();

    send_BEGIN(type, "cpu_user", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, (kernel_uint_t)(w->utime * utime_fix_ratio) + (include_exited_childs?((kernel_uint_t)(w->cutime * cutime_fix_ratio)):0ULL));
    }
    send_END();

    send_BEGIN(type, "cpu_system", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, (kernel_uint_t)(w->stime * stime_fix_ratio) + (include_exited_childs?((kernel_uint_t)(w->cstime * cstime_fix_ratio)):0ULL));
    }
    send_END();

    if(show_guest_time) {
        send_BEGIN(type, "cpu_guest", dt);
        for (w = root; w ; w = w->next) {
            if(unlikely(w->exposed && w->processes))
                send_SET(w->name, (kernel_uint_t)(w->gtime * gtime_fix_ratio) + (include_exited_childs?((kernel_uint_t)(w->cgtime * cgtime_fix_ratio)):0ULL));
        }
        send_END();
    }

    send_BEGIN(type, "threads", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->num_threads);
    }
    send_END();

    send_BEGIN(type, "processes", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->processes);
    }
    send_END();

#ifndef __FreeBSD__
    send_BEGIN(type, "uptime", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, (global_uptime > w->starttime)?(global_uptime - w->starttime):0);
    }
    send_END();

    send_BEGIN(type, "uptime_min", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->uptime_min);
    }
    send_END();

    send_BEGIN(type, "uptime_avg", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->uptime_sum / w->processes);
    }
    send_END();

    send_BEGIN(type, "uptime_max", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->uptime_max);
    }
    send_END();
#endif

    send_BEGIN(type, "mem", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, (w->status_vmrss > w->status_vmshared)?(w->status_vmrss - w->status_vmshared):0ULL);
    }
    send_END();

    send_BEGIN(type, "vmem", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->status_vmsize);
    }
    send_END();

#ifndef __FreeBSD__
    send_BEGIN(type, "swap", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->status_vmswap);
    }
    send_END();
#endif

    send_BEGIN(type, "minor_faults", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, (kernel_uint_t)(w->minflt * minflt_fix_ratio) + (include_exited_childs?((kernel_uint_t)(w->cminflt * cminflt_fix_ratio)):0ULL));
    }
    send_END();

    send_BEGIN(type, "major_faults", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, (kernel_uint_t)(w->majflt * majflt_fix_ratio) + (include_exited_childs?((kernel_uint_t)(w->cmajflt * cmajflt_fix_ratio)):0ULL));
    }
    send_END();

#ifndef __FreeBSD__
    send_BEGIN(type, "lreads", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->io_logical_bytes_read);
    }
    send_END();

    send_BEGIN(type, "lwrites", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->io_logical_bytes_written);
    }
    send_END();
#endif

    send_BEGIN(type, "preads", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->io_storage_bytes_read);
    }
    send_END();

    send_BEGIN(type, "pwrites", dt);
    for (w = root; w ; w = w->next) {
        if(unlikely(w->exposed && w->processes))
            send_SET(w->name, w->io_storage_bytes_written);
    }
    send_END();

    if(enable_file_charts) {
        send_BEGIN(type, "files", dt);
        for (w = root; w; w = w->next) {
            if (unlikely(w->exposed && w->processes))
                send_SET(w->name, w->openfiles);
        }
        send_END();

        send_BEGIN(type, "sockets", dt);
        for (w = root; w; w = w->next) {
            if (unlikely(w->exposed && w->processes))
                send_SET(w->name, w->opensockets);
        }
        send_END();

        send_BEGIN(type, "pipes", dt);
        for (w = root; w; w = w->next) {
            if (unlikely(w->exposed && w->processes))
                send_SET(w->name, w->openpipes);
        }
        send_END();
    }
}