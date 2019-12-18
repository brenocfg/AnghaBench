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
struct file {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CAP_FILE_BUFFER ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_RD ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_SHARED ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_WR ; 
 int EAGAIN ; 
 int ceph_get_caps (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_put_cap_refs (int /*<<< orphan*/ ,int) ; 
 int ceph_try_get_caps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 

__attribute__((used)) static int get_rd_wr_caps(struct file *src_filp, int *src_got,
			  struct file *dst_filp,
			  loff_t dst_endoff, int *dst_got)
{
	int ret = 0;
	bool retrying = false;

retry_caps:
	ret = ceph_get_caps(dst_filp, CEPH_CAP_FILE_WR, CEPH_CAP_FILE_BUFFER,
			    dst_endoff, dst_got, NULL);
	if (ret < 0)
		return ret;

	/*
	 * Since we're already holding the FILE_WR capability for the dst file,
	 * we would risk a deadlock by using ceph_get_caps.  Thus, we'll do some
	 * retry dance instead to try to get both capabilities.
	 */
	ret = ceph_try_get_caps(file_inode(src_filp),
				CEPH_CAP_FILE_RD, CEPH_CAP_FILE_SHARED,
				false, src_got);
	if (ret <= 0) {
		/* Start by dropping dst_ci caps and getting src_ci caps */
		ceph_put_cap_refs(ceph_inode(file_inode(dst_filp)), *dst_got);
		if (retrying) {
			if (!ret)
				/* ceph_try_get_caps masks EAGAIN */
				ret = -EAGAIN;
			return ret;
		}
		ret = ceph_get_caps(src_filp, CEPH_CAP_FILE_RD,
				    CEPH_CAP_FILE_SHARED, -1, src_got, NULL);
		if (ret < 0)
			return ret;
		/*... drop src_ci caps too, and retry */
		ceph_put_cap_refs(ceph_inode(file_inode(src_filp)), *src_got);
		retrying = true;
		goto retry_caps;
	}
	return ret;
}