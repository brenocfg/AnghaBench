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
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int acpi_aml_set_fl(int fd, int flags)
{
	int ret;

	ret = fcntl(fd, F_GETFL, 0);
	if (ret < 0) {
		perror("fcntl(F_GETFL)");
		return ret;
	}
	flags |= ret;
	ret = fcntl(fd, F_SETFL, flags);
	if (ret < 0) {
		perror("fcntl(F_SETFL)");
		return ret;
	}
	return ret;
}