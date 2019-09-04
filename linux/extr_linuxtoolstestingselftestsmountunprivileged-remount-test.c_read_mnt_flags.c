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
struct statvfs {int f_flag; } ;

/* Variables and functions */
 int MS_NOATIME ; 
 int MS_NODEV ; 
 int MS_NODIRATIME ; 
 int MS_NOEXEC ; 
 int MS_NOSUID ; 
 int MS_RDONLY ; 
 int MS_RELATIME ; 
 int MS_SYNCHRONOUS ; 
 int ST_MANDLOCK ; 
 int ST_NOATIME ; 
 int ST_NODEV ; 
 int ST_NODIRATIME ; 
 int ST_NOEXEC ; 
 int ST_NOSUID ; 
 int ST_RDONLY ; 
 int ST_RELATIME ; 
 int ST_SYNCHRONOUS ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int statvfs (char const*,struct statvfs*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_mnt_flags(const char *path)
{
	int ret;
	struct statvfs stat;
	int mnt_flags;

	ret = statvfs(path, &stat);
	if (ret != 0) {
		die("statvfs of %s failed: %s\n",
			path, strerror(errno));
	}
	if (stat.f_flag & ~(ST_RDONLY | ST_NOSUID | ST_NODEV | \
			ST_NOEXEC | ST_NOATIME | ST_NODIRATIME | ST_RELATIME | \
			ST_SYNCHRONOUS | ST_MANDLOCK)) {
		die("Unrecognized mount flags\n");
	}
	mnt_flags = 0;
	if (stat.f_flag & ST_RDONLY)
		mnt_flags |= MS_RDONLY;
	if (stat.f_flag & ST_NOSUID)
		mnt_flags |= MS_NOSUID;
	if (stat.f_flag & ST_NODEV)
		mnt_flags |= MS_NODEV;
	if (stat.f_flag & ST_NOEXEC)
		mnt_flags |= MS_NOEXEC;
	if (stat.f_flag & ST_NOATIME)
		mnt_flags |= MS_NOATIME;
	if (stat.f_flag & ST_NODIRATIME)
		mnt_flags |= MS_NODIRATIME;
	if (stat.f_flag & ST_RELATIME)
		mnt_flags |= MS_RELATIME;
	if (stat.f_flag & ST_SYNCHRONOUS)
		mnt_flags |= MS_SYNCHRONOUS;
	if (stat.f_flag & ST_MANDLOCK)
		mnt_flags |= ST_MANDLOCK;

	return mnt_flags;
}