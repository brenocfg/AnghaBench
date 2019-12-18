#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pid_stat {scalar_t__ io_storage_bytes_written; scalar_t__ io_storage_bytes_read; scalar_t__ io_logical_bytes_written; scalar_t__ io_logical_bytes_read; int /*<<< orphan*/  io_collected_usec; int /*<<< orphan*/  last_io_collected_usec; int /*<<< orphan*/  io_filename; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  ru_oublock; int /*<<< orphan*/  ru_inblock; } ;
struct kinfo_proc {TYPE_1__ ki_rusage; } ;
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  PROCFILE_FLAG_NO_ERROR_ON_FILE_IO ; 
 int /*<<< orphan*/  calls_counter ; 
 int global_iterations_counter ; 
 int /*<<< orphan*/  io ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 int /*<<< orphan*/  now_monotonic_usec () ; 
 int /*<<< orphan*/  pid_incremental_rate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfile_lineword (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * procfile_reopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str2kernel_uint_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int read_proc_pid_io(struct pid_stat *p, void *ptr) {
    (void)ptr;
#ifdef __FreeBSD__
    struct kinfo_proc *proc_info = (struct kinfo_proc *)ptr;
#else
    static procfile *ff = NULL;

    if(unlikely(!p->io_filename)) {
        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s/proc/%d/io", netdata_configured_host_prefix, p->pid);
        p->io_filename = strdupz(filename);
    }

    // open the file
    ff = procfile_reopen(ff, p->io_filename, NULL, PROCFILE_FLAG_NO_ERROR_ON_FILE_IO);
    if(unlikely(!ff)) goto cleanup;

    ff = procfile_readall(ff);
    if(unlikely(!ff)) goto cleanup;
#endif

    calls_counter++;

    p->last_io_collected_usec = p->io_collected_usec;
    p->io_collected_usec = now_monotonic_usec();

#ifdef __FreeBSD__
    pid_incremental_rate(io, p->io_storage_bytes_read,       proc_info->ki_rusage.ru_inblock);
    pid_incremental_rate(io, p->io_storage_bytes_written,    proc_info->ki_rusage.ru_oublock);
#else
    pid_incremental_rate(io, p->io_logical_bytes_read,       str2kernel_uint_t(procfile_lineword(ff, 0,  1)));
    pid_incremental_rate(io, p->io_logical_bytes_written,    str2kernel_uint_t(procfile_lineword(ff, 1,  1)));
    // pid_incremental_rate(io, p->io_read_calls,               str2kernel_uint_t(procfile_lineword(ff, 2,  1)));
    // pid_incremental_rate(io, p->io_write_calls,              str2kernel_uint_t(procfile_lineword(ff, 3,  1)));
    pid_incremental_rate(io, p->io_storage_bytes_read,       str2kernel_uint_t(procfile_lineword(ff, 4,  1)));
    pid_incremental_rate(io, p->io_storage_bytes_written,    str2kernel_uint_t(procfile_lineword(ff, 5,  1)));
    // pid_incremental_rate(io, p->io_cancelled_write_bytes,    str2kernel_uint_t(procfile_lineword(ff, 6,  1)));
#endif

    if(unlikely(global_iterations_counter == 1)) {
        p->io_logical_bytes_read        = 0;
        p->io_logical_bytes_written     = 0;
        // p->io_read_calls             = 0;
        // p->io_write_calls            = 0;
        p->io_storage_bytes_read        = 0;
        p->io_storage_bytes_written     = 0;
        // p->io_cancelled_write_bytes  = 0;
    }

    return 1;

#ifndef __FreeBSD__
cleanup:
    p->io_logical_bytes_read        = 0;
    p->io_logical_bytes_written     = 0;
    // p->io_read_calls             = 0;
    // p->io_write_calls            = 0;
    p->io_storage_bytes_read        = 0;
    p->io_storage_bytes_written     = 0;
    // p->io_cancelled_write_bytes  = 0;
    return 0;
#endif
}