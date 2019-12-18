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
struct subprocess_info {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int CLONE_FILES ; 
 int CLONE_FS ; 
 int /*<<< orphan*/  MS_MOVE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  ksys_chdir (char*) ; 
 int /*<<< orphan*/  ksys_chroot (char*) ; 
 int /*<<< orphan*/  ksys_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksys_mount (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksys_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksys_setsid () ; 
 int /*<<< orphan*/  ksys_unshare (int) ; 

__attribute__((used)) static int init_linuxrc(struct subprocess_info *info, struct cred *new)
{
	ksys_unshare(CLONE_FS | CLONE_FILES);
	/* stdin/stdout/stderr for /linuxrc */
	ksys_open("/dev/console", O_RDWR, 0);
	ksys_dup(0);
	ksys_dup(0);
	/* move initrd over / and chdir/chroot in initrd root */
	ksys_chdir("/root");
	ksys_mount(".", "/", NULL, MS_MOVE, NULL);
	ksys_chroot(".");
	ksys_setsid();
	return 0;
}