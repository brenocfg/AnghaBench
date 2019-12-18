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
typedef  int umode_t ;
typedef  int u32 ;
struct v9fs_session_info {scalar_t__ nodev; } ;

/* Variables and functions */
 int P9_DMDEVICE ; 
 int P9_DMDIR ; 
 int P9_DMNAMEDPIPE ; 
 int P9_DMSETGID ; 
 int P9_DMSETUID ; 
 int P9_DMSETVTX ; 
 int P9_DMSOCKET ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 int S_ISGID ; 
 scalar_t__ S_ISSOCK (int) ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 scalar_t__ v9fs_proto_dotu (struct v9fs_session_info*) ; 

__attribute__((used)) static u32 unixmode2p9mode(struct v9fs_session_info *v9ses, umode_t mode)
{
	int res;
	res = mode & 0777;
	if (S_ISDIR(mode))
		res |= P9_DMDIR;
	if (v9fs_proto_dotu(v9ses)) {
		if (v9ses->nodev == 0) {
			if (S_ISSOCK(mode))
				res |= P9_DMSOCKET;
			if (S_ISFIFO(mode))
				res |= P9_DMNAMEDPIPE;
			if (S_ISBLK(mode))
				res |= P9_DMDEVICE;
			if (S_ISCHR(mode))
				res |= P9_DMDEVICE;
		}

		if ((mode & S_ISUID) == S_ISUID)
			res |= P9_DMSETUID;
		if ((mode & S_ISGID) == S_ISGID)
			res |= P9_DMSETGID;
		if ((mode & S_ISVTX) == S_ISVTX)
			res |= P9_DMSETVTX;
	}
	return res;
}