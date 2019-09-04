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
 int /*<<< orphan*/  WDIOC_KEEPALIVE ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void keep_alive(void)
{
	int dummy;
	int ret;

	ret = ioctl(fd, WDIOC_KEEPALIVE, &dummy);
	if (!ret)
		printf(".");
}