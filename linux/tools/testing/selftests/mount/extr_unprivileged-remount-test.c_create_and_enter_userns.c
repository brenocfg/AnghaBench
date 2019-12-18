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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_NEWUSER ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  maybe_write_file (char*,char*) ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ unshare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_file (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_and_enter_userns(void)
{
	uid_t uid;
	gid_t gid;

	uid = getuid();
	gid = getgid();

	if (unshare(CLONE_NEWUSER) !=0) {
		die("unshare(CLONE_NEWUSER) failed: %s\n",
			strerror(errno));
	}

	maybe_write_file("/proc/self/setgroups", "deny");
	write_file("/proc/self/uid_map", "0 %d 1", uid);
	write_file("/proc/self/gid_map", "0 %d 1", gid);

	if (setgid(0) != 0) {
		die ("setgid(0) failed %s\n",
			strerror(errno));
	}
	if (setuid(0) != 0) {
		die("setuid(0) failed %s\n",
			strerror(errno));
	}
}