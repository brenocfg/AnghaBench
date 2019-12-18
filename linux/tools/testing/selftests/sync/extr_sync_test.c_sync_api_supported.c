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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void sync_api_supported(void)
{
	struct stat sbuf;
	int ret;

	ret = stat("/sys/kernel/debug/sync/sw_sync", &sbuf);
	if (!ret)
		return;

	if (errno == ENOENT)
		ksft_exit_skip("Sync framework not supported by kernel\n");

	if (errno == EACCES)
		ksft_exit_skip("Run Sync test as root.\n");

	ksft_exit_fail_msg("stat failed on /sys/kernel/debug/sync/sw_sync: %s",
				strerror(errno));
}