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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 unsigned long F2FS_APPEND_FL ; 
 unsigned long F2FS_IMMUTABLE_FL ; 
 unsigned long F2FS_NOATIME_FL ; 
 unsigned long F2FS_NODUMP_FL ; 
 unsigned long F2FS_PROJINHERIT_FL ; 
 unsigned long F2FS_SYNC_FL ; 
 int /*<<< orphan*/  FS_XFLAG_APPEND ; 
 int /*<<< orphan*/  FS_XFLAG_IMMUTABLE ; 
 int /*<<< orphan*/  FS_XFLAG_NOATIME ; 
 int /*<<< orphan*/  FS_XFLAG_NODUMP ; 
 int /*<<< orphan*/  FS_XFLAG_PROJINHERIT ; 
 int /*<<< orphan*/  FS_XFLAG_SYNC ; 

__attribute__((used)) static inline __u32 f2fs_iflags_to_xflags(unsigned long iflags)
{
	__u32 xflags = 0;

	if (iflags & F2FS_SYNC_FL)
		xflags |= FS_XFLAG_SYNC;
	if (iflags & F2FS_IMMUTABLE_FL)
		xflags |= FS_XFLAG_IMMUTABLE;
	if (iflags & F2FS_APPEND_FL)
		xflags |= FS_XFLAG_APPEND;
	if (iflags & F2FS_NODUMP_FL)
		xflags |= FS_XFLAG_NODUMP;
	if (iflags & F2FS_NOATIME_FL)
		xflags |= FS_XFLAG_NOATIME;
	if (iflags & F2FS_PROJINHERIT_FL)
		xflags |= FS_XFLAG_PROJINHERIT;
	return xflags;
}