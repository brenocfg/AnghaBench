#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int /*<<< orphan*/  time_stamp; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ zend_perf_jitdump_record ;
typedef  int /*<<< orphan*/  rec ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  ZEND_PERF_JITDUMP_RECORD_CLOSE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ jitdump_fd ; 
 scalar_t__ jitdump_mem ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_perf_timestamp () ; 
 int /*<<< orphan*/  zend_quiet_write (scalar_t__,TYPE_1__*,int) ; 

__attribute__((used)) static void zend_jit_perf_jitdump_close(void)
{
	if (jitdump_fd >= 0) {
		zend_perf_jitdump_record rec;

		rec.event      = ZEND_PERF_JITDUMP_RECORD_CLOSE;
		rec.size       = sizeof(rec);
		rec.time_stamp = zend_perf_timestamp();
		zend_quiet_write(jitdump_fd, &rec, sizeof(rec));
		close(jitdump_fd);

		if (jitdump_mem != MAP_FAILED) {
			munmap(jitdump_mem, sysconf(_SC_PAGESIZE));
		}
	}
}