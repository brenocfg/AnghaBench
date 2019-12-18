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
 int /*<<< orphan*/  DEBUG_PRINT_L3 (char*,int) ; 
 int /*<<< orphan*/  DEBUG_PRINT_T (char*,long) ; 
 int /*<<< orphan*/  RDTICK (long) ; 
 int errno ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  read_stats ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,long,int) ; 

__attribute__((used)) static int read_adi(int fd, unsigned char *buf, int buf_sz)
{
	int ret, bytes_read = 0;
	long start, end, elapsed_time = 0;

	do {
		RDTICK(start);
		ret = read(fd, buf + bytes_read, buf_sz - bytes_read);
		RDTICK(end);
		if (ret < 0)
			return -errno;

		elapsed_time += end - start;
		update_stats(&read_stats, elapsed_time, buf_sz);
		bytes_read += ret;

	} while (bytes_read < buf_sz);

	DEBUG_PRINT_T("\tread elapsed timed = %ld\n", elapsed_time);
	DEBUG_PRINT_L3("\tRead  %d bytes\n", bytes_read);

	return bytes_read;
}