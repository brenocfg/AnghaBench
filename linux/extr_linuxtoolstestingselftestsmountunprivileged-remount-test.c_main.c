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
 int EXIT_SUCCESS ; 
 int MS_NOATIME ; 
 int MS_NODEV ; 
 int MS_NODIRATIME ; 
 int /*<<< orphan*/  MS_NOEXEC ; 
 int /*<<< orphan*/  MS_NOSUID ; 
 int /*<<< orphan*/  MS_RDONLY ; 
 int MS_RELATIME ; 
 int MS_STRICTATIME ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  test_priv_mount_unpriv_remount () ; 
 int /*<<< orphan*/  test_unpriv_remount (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  test_unpriv_remount_atime (int,int) ; 
 int /*<<< orphan*/  test_unpriv_remount_simple (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	if (!test_unpriv_remount_simple(MS_RDONLY)) {
		die("MS_RDONLY malfunctions\n");
	}
	if (!test_unpriv_remount("devpts", "newinstance", MS_NODEV, MS_NODEV, 0)) {
		die("MS_NODEV malfunctions\n");
	}
	if (!test_unpriv_remount_simple(MS_NOSUID)) {
		die("MS_NOSUID malfunctions\n");
	}
	if (!test_unpriv_remount_simple(MS_NOEXEC)) {
		die("MS_NOEXEC malfunctions\n");
	}
	if (!test_unpriv_remount_atime(MS_RELATIME,
				       MS_NOATIME))
	{
		die("MS_RELATIME malfunctions\n");
	}
	if (!test_unpriv_remount_atime(MS_STRICTATIME,
				       MS_NOATIME))
	{
		die("MS_STRICTATIME malfunctions\n");
	}
	if (!test_unpriv_remount_atime(MS_NOATIME,
				       MS_STRICTATIME))
	{
		die("MS_NOATIME malfunctions\n");
	}
	if (!test_unpriv_remount_atime(MS_RELATIME|MS_NODIRATIME,
				       MS_NOATIME))
	{
		die("MS_RELATIME|MS_NODIRATIME malfunctions\n");
	}
	if (!test_unpriv_remount_atime(MS_STRICTATIME|MS_NODIRATIME,
				       MS_NOATIME))
	{
		die("MS_STRICTATIME|MS_NODIRATIME malfunctions\n");
	}
	if (!test_unpriv_remount_atime(MS_NOATIME|MS_NODIRATIME,
				       MS_STRICTATIME))
	{
		die("MS_NOATIME|MS_DIRATIME malfunctions\n");
	}
	if (!test_unpriv_remount("ramfs", NULL, MS_STRICTATIME, 0, MS_NOATIME))
	{
		die("Default atime malfunctions\n");
	}
	if (!test_priv_mount_unpriv_remount()) {
		die("Mount flags unexpectedly changed after remount\n");
	}
	return EXIT_SUCCESS;
}