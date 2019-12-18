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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int EINVAL ; 
 int OCFS2_ORPHAN_NAMELEN ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int snprintf (char*,int,char*,long long) ; 
 int /*<<< orphan*/  trace_ocfs2_blkno_stringify (scalar_t__,char*,int) ; 

__attribute__((used)) static int ocfs2_blkno_stringify(u64 blkno, char *name)
{
	int status, namelen;

	namelen = snprintf(name, OCFS2_ORPHAN_NAMELEN + 1, "%016llx",
			   (long long)blkno);
	if (namelen <= 0) {
		if (namelen)
			status = namelen;
		else
			status = -EINVAL;
		mlog_errno(status);
		goto bail;
	}
	if (namelen != OCFS2_ORPHAN_NAMELEN) {
		status = -EINVAL;
		mlog_errno(status);
		goto bail;
	}

	trace_ocfs2_blkno_stringify(blkno, name, namelen);

	status = 0;
bail:
	if (status < 0)
		mlog_errno(status);
	return status;
}