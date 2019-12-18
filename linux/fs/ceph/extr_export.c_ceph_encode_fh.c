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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct ceph_nfs_fh {void* ino; } ;
struct ceph_nfs_confh {void* parent_ino; void* ino; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int FILEID_INO32_GEN ; 
 int FILEID_INO32_GEN_PARENT ; 
 int FILEID_INVALID ; 
 int ceph_encode_snapfh (struct inode*,int /*<<< orphan*/ *,int*,struct inode*) ; 
 void* ceph_ino (struct inode*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,void*,...) ; 

__attribute__((used)) static int ceph_encode_fh(struct inode *inode, u32 *rawfh, int *max_len,
			  struct inode *parent_inode)
{
	static const int handle_length =
		sizeof(struct ceph_nfs_fh) >> 2;
	static const int connected_handle_length =
		sizeof(struct ceph_nfs_confh) >> 2;
	int type;

	if (ceph_snap(inode) != CEPH_NOSNAP)
		return ceph_encode_snapfh(inode, rawfh, max_len, parent_inode);

	if (parent_inode && (*max_len < connected_handle_length)) {
		*max_len = connected_handle_length;
		return FILEID_INVALID;
	} else if (*max_len < handle_length) {
		*max_len = handle_length;
		return FILEID_INVALID;
	}

	if (parent_inode) {
		struct ceph_nfs_confh *cfh = (void *)rawfh;
		dout("encode_fh %llx with parent %llx\n",
		     ceph_ino(inode), ceph_ino(parent_inode));
		cfh->ino = ceph_ino(inode);
		cfh->parent_ino = ceph_ino(parent_inode);
		*max_len = connected_handle_length;
		type = FILEID_INO32_GEN_PARENT;
	} else {
		struct ceph_nfs_fh *fh = (void *)rawfh;
		dout("encode_fh %llx\n", ceph_ino(inode));
		fh->ino = ceph_ino(inode);
		*max_len = handle_length;
		type = FILEID_INO32_GEN;
	}
	return type;
}