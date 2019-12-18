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
 int /*<<< orphan*/  DEBUG_PRINT_L3 (char*,int,int) ; 
 int /*<<< orphan*/  DEBUG_PRINT_T (char*,long) ; 
 int /*<<< orphan*/  RDTICK (long) ; 
 int errno ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,long,int) ; 
 int write (int,unsigned char const* const,int) ; 
 int /*<<< orphan*/  write_stats ; 

__attribute__((used)) static int write_adi(int fd, const unsigned char * const buf, int buf_sz)
{
	int ret, bytes_written = 0;
	long start, end, elapsed_time = 0;

	do {
		RDTICK(start);
		ret = write(fd, buf + bytes_written, buf_sz - bytes_written);
		RDTICK(end);
		if (ret < 0)
			return -errno;

		elapsed_time += (end - start);
		update_stats(&write_stats, elapsed_time, buf_sz);
		bytes_written += ret;
	} while (bytes_written < buf_sz);

	DEBUG_PRINT_T("\twrite elapsed timed = %ld\n", elapsed_time);
	DEBUG_PRINT_L3("\tWrote %d of %d bytes\n", bytes_written, buf_sz);

	return bytes_written;
}