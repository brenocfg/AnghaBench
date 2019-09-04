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
typedef  unsigned long off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 long bounds_dir_global ; 
 unsigned long lseek (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpx_dig_abort () ; 
 int /*<<< orphan*/  proc_pid_mem_fd ; 
 int read (int /*<<< orphan*/ ,void*,long) ; 

void *fill_bounds_dir_buf_other(long byte_offset_inside_bounds_dir,
			   long buffer_size_bytes, void *buffer)
{
	unsigned long seekto = bounds_dir_global + byte_offset_inside_bounds_dir;
	int read_ret;
	off_t seek_ret = lseek(proc_pid_mem_fd, seekto, SEEK_SET);

	if (seek_ret != seekto)
		mpx_dig_abort();

	read_ret = read(proc_pid_mem_fd, buffer, buffer_size_bytes);
	/* there shouldn't practically be short reads of /proc/$pid/mem */
	if (read_ret != buffer_size_bytes)
		mpx_dig_abort();

	return buffer;
}