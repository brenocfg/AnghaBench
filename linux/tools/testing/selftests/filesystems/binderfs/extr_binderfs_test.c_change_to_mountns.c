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
 int /*<<< orphan*/  CLONE_NEWNS ; 
 int MS_PRIVATE ; 
 int MS_REC ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 int mount (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int unshare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void change_to_mountns(void)
{
	int ret;

	ret = unshare(CLONE_NEWNS);
	if (ret < 0)
		ksft_exit_fail_msg("%s - Failed to unshare mount namespace\n",
				   strerror(errno));

	ret = mount(NULL, "/", NULL, MS_REC | MS_PRIVATE, 0);
	if (ret < 0)
		ksft_exit_fail_msg("%s - Failed to mount / as private\n",
				   strerror(errno));
}