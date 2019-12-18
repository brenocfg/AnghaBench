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
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int read (int,long long*,int) ; 

__attribute__((used)) static int wp_read(int fd, long long *count, int size)
{
	int ret = read(fd, count, size);

	if (ret != size) {
		pr_debug("failed to read: %d\n", ret);
		return -1;
	}
	return 0;
}