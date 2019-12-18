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
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 int MS_PRIVATE ; 
 int MS_REC ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int mount (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ *) ; 
 int unshare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void make_private_tmp(void)
{
	if (unshare(CLONE_NEWNS) == -1) {
		if (errno == ENOSYS || errno == EPERM) {
			exit(4);
		}
		exit(1);
	}
	if (mount(NULL, "/", NULL, MS_PRIVATE|MS_REC, NULL) == -1) {
		exit(1);
	}
	if (mount(NULL, "/tmp", "tmpfs", 0, NULL) == -1) {
		exit(1);
	}
}