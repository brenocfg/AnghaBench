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
struct pid_stat {int status_vmsize; int status_vmrss; scalar_t__ status_rssshmem; scalar_t__ status_rssfile; scalar_t__ status_vmshared; scalar_t__ status_arl; int /*<<< orphan*/  status_filename; int /*<<< orphan*/  pid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; scalar_t__ status_vmswap; } ;
struct kinfo_proc {int ki_size; int ki_rssize; int /*<<< orphan*/ * ki_groups; int /*<<< orphan*/  ki_uid; } ;
struct arl_callback_ptr {size_t line; int /*<<< orphan*/ * ff; struct pid_stat* p; } ;
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  PROCFILE_FLAG_NO_ERROR_ON_FILE_IO ; 
 int /*<<< orphan*/  arl_begin (scalar_t__) ; 
 int /*<<< orphan*/  arl_callback_status_gid ; 
 int /*<<< orphan*/  arl_callback_status_rssfile ; 
 int /*<<< orphan*/  arl_callback_status_rssshmem ; 
 int /*<<< orphan*/  arl_callback_status_uid ; 
 int /*<<< orphan*/  arl_callback_status_vmrss ; 
 int /*<<< orphan*/  arl_callback_status_vmsize ; 
 int /*<<< orphan*/  arl_callback_status_vmswap ; 
 int arl_check (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ arl_create (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  arl_expect_custom (scalar_t__,char*,int /*<<< orphan*/ ,struct arl_callback_ptr*) ; 
 int /*<<< orphan*/  calls_counter ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 int pagesize ; 
 size_t procfile_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfile_lineword (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * procfile_reopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int read_proc_pid_status(struct pid_stat *p, void *ptr) {
    p->status_vmsize           = 0;
    p->status_vmrss            = 0;
    p->status_vmshared         = 0;
    p->status_rssfile          = 0;
    p->status_rssshmem         = 0;
    p->status_vmswap           = 0;

#ifdef __FreeBSD__
    struct kinfo_proc *proc_info = (struct kinfo_proc *)ptr;

    p->uid                  = proc_info->ki_uid;
    p->gid                  = proc_info->ki_groups[0];
    p->status_vmsize        = proc_info->ki_size / 1024; // in KiB
    p->status_vmrss         = proc_info->ki_rssize * pagesize / 1024; // in KiB
    // TODO: what about shared and swap memory on FreeBSD?
    return 1;
#else
    (void)ptr;

    static struct arl_callback_ptr arl_ptr;
    static procfile *ff = NULL;

    if(unlikely(!p->status_arl)) {
        p->status_arl = arl_create("/proc/pid/status", NULL, 60);
        arl_expect_custom(p->status_arl, "Uid", arl_callback_status_uid, &arl_ptr);
        arl_expect_custom(p->status_arl, "Gid", arl_callback_status_gid, &arl_ptr);
        arl_expect_custom(p->status_arl, "VmSize", arl_callback_status_vmsize, &arl_ptr);
        arl_expect_custom(p->status_arl, "VmRSS", arl_callback_status_vmrss, &arl_ptr);
        arl_expect_custom(p->status_arl, "RssFile", arl_callback_status_rssfile, &arl_ptr);
        arl_expect_custom(p->status_arl, "RssShmem", arl_callback_status_rssshmem, &arl_ptr);
        arl_expect_custom(p->status_arl, "VmSwap", arl_callback_status_vmswap, &arl_ptr);
    }

    if(unlikely(!p->status_filename)) {
        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s/proc/%d/status", netdata_configured_host_prefix, p->pid);
        p->status_filename = strdupz(filename);
    }

    ff = procfile_reopen(ff, p->status_filename, (!ff)?" \t:,-()/":NULL, PROCFILE_FLAG_NO_ERROR_ON_FILE_IO);
    if(unlikely(!ff)) return 0;

    ff = procfile_readall(ff);
    if(unlikely(!ff)) return 0;

    calls_counter++;

    // let ARL use this pid
    arl_ptr.p = p;
    arl_ptr.ff = ff;

    size_t lines = procfile_lines(ff), l;
    arl_begin(p->status_arl);

    for(l = 0; l < lines ;l++) {
        // debug_log("CHECK: line %zu of %zu, key '%s' = '%s'", l, lines, procfile_lineword(ff, l, 0), procfile_lineword(ff, l, 1));
        arl_ptr.line = l;
        if(unlikely(arl_check(p->status_arl,
                procfile_lineword(ff, l, 0),
                procfile_lineword(ff, l, 1)))) break;
    }

    p->status_vmshared = p->status_rssfile + p->status_rssshmem;

    // debug_log("%s uid %d, gid %d, VmSize %zu, VmRSS %zu, RssFile %zu, RssShmem %zu, shared %zu", p->comm, (int)p->uid, (int)p->gid, p->status_vmsize, p->status_vmrss, p->status_rssfile, p->status_rssshmem, p->status_vmshared);

    return 1;
#endif
}