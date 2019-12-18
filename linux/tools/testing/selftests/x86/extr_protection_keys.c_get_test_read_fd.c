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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  __save_test_fd (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

int get_test_read_fd(void)
{
	int test_fd = open("/etc/passwd", O_RDONLY);
	__save_test_fd(test_fd);
	return test_fd;
}