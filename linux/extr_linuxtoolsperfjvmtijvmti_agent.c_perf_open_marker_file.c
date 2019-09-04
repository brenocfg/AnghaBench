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

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 scalar_t__ marker_addr ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,long,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
perf_open_marker_file(int fd)
{
	long pgsz;

	pgsz = sysconf(_SC_PAGESIZE);
	if (pgsz == -1)
		return -1;

	/*
	 * we mmap the jitdump to create an MMAP RECORD in perf.data file.
	 * The mmap is captured either live (perf record running when we mmap)
	 * or  in deferred mode, via /proc/PID/maps
	 * the MMAP record is used as a marker of a jitdump file for more meta
	 * data info about the jitted code. Perf report/annotate detect this
	 * special filename and process the jitdump file.
	 *
	 * mapping must be PROT_EXEC to ensure it is captured by perf record
	 * even when not using -d option
	 */
	marker_addr = mmap(NULL, pgsz, PROT_READ|PROT_EXEC, MAP_PRIVATE, fd, 0);
	return (marker_addr == MAP_FAILED) ? -1 : 0;
}