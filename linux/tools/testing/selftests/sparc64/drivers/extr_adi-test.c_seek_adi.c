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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT_L2 (char*,scalar_t__) ; 
 int /*<<< orphan*/  DEBUG_PRINT_T (char*,long) ; 
 int /*<<< orphan*/  RDTICK (long) ; 
 int SEEK_END ; 
 scalar_t__ lseek (int,scalar_t__,int) ; 
 int /*<<< orphan*/  seek_stats ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t seek_adi(int fd, off_t offset, int whence)
{
	long start, end;
	off_t ret;

	RDTICK(start);
	ret = lseek(fd, offset, whence);
	RDTICK(end);
	DEBUG_PRINT_L2("\tlseek ret = 0x%llx\n", ret);
	if (ret < 0)
		goto out;

	DEBUG_PRINT_T("\tlseek elapsed timed = %ld\n", end - start);
	update_stats(&seek_stats, end - start, 0);

out:
	(void)lseek(fd, 0, SEEK_END);
	return ret;
}