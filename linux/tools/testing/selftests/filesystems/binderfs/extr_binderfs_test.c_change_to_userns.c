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
typedef  int uid_t ;
typedef  int /*<<< orphan*/  idmap ;
typedef  int gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_NEWUSER ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  errno ; 
 int getgid () ; 
 int getuid () ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 int setgid (int /*<<< orphan*/ ) ; 
 int setuid (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int unshare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_to_file (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void change_to_userns(void)
{
	int ret;
	uid_t uid;
	gid_t gid;
	/* {g,u}id_map files only allow a max of 4096 bytes written to them */
	char idmap[4096];

	uid = getuid();
	gid = getgid();

	ret = unshare(CLONE_NEWUSER);
	if (ret < 0)
		ksft_exit_fail_msg("%s - Failed to unshare user namespace\n",
				   strerror(errno));

	write_to_file("/proc/self/setgroups", "deny", strlen("deny"), ENOENT);

	ret = snprintf(idmap, sizeof(idmap), "0 %d 1", uid);
	if (ret < 0 || (size_t)ret >= sizeof(idmap))
		ksft_exit_fail_msg("%s - Failed to prepare uid mapping\n",
				   strerror(errno));

	write_to_file("/proc/self/uid_map", idmap, strlen(idmap), 0);

	ret = snprintf(idmap, sizeof(idmap), "0 %d 1", gid);
	if (ret < 0 || (size_t)ret >= sizeof(idmap))
		ksft_exit_fail_msg("%s - Failed to prepare uid mapping\n",
				   strerror(errno));

	write_to_file("/proc/self/gid_map", idmap, strlen(idmap), 0);

	ret = setgid(0);
	if (ret)
		ksft_exit_fail_msg("%s - Failed to setgid(0)\n",
				   strerror(errno));

	ret = setuid(0);
	if (ret)
		ksft_exit_fail_msg("%s - Failed to setgid(0)\n",
				   strerror(errno));
}