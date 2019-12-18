#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {struct super_block* mnt_sb; } ;
struct tm {scalar_t__ tm_year; } ;
struct super_block {scalar_t__ s_time_max; TYPE_1__* s_type; } ;
struct path {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ TIME_UPTIME_SEC_MAX ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mnt_is_readonly (struct vfsmount*) ; 
 char* d_path (struct path*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,char*,scalar_t__,unsigned long long) ; 
 int /*<<< orphan*/  time64_to_tm (scalar_t__,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static void mnt_warn_timestamp_expiry(struct path *mountpoint, struct vfsmount *mnt)
{
	struct super_block *sb = mnt->mnt_sb;

	if (!__mnt_is_readonly(mnt) &&
	   (ktime_get_real_seconds() + TIME_UPTIME_SEC_MAX > sb->s_time_max)) {
		char *buf = (char *)__get_free_page(GFP_KERNEL);
		char *mntpath = buf ? d_path(mountpoint, buf, PAGE_SIZE) : ERR_PTR(-ENOMEM);
		struct tm tm;

		time64_to_tm(sb->s_time_max, 0, &tm);

		pr_warn("Mounted %s file system at %s supports timestamps until %04ld (0x%llx)\n",
			sb->s_type->name, mntpath,
			tm.tm_year+1900, (unsigned long long)sb->s_time_max);

		free_page((unsigned long)buf);
	}
}