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
struct iso_inode_info {scalar_t__ i_iget5_offset; int /*<<< orphan*/  i_iget5_block; } ;
struct inode {int /*<<< orphan*/  i_generation; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int FILEID_INVALID ; 
 struct iso_inode_info* ISOFS_I (struct inode*) ; 

__attribute__((used)) static int
isofs_export_encode_fh(struct inode *inode,
		       __u32 *fh32,
		       int *max_len,
		       struct inode *parent)
{
	struct iso_inode_info * ei = ISOFS_I(inode);
	int len = *max_len;
	int type = 1;
	__u16 *fh16 = (__u16*)fh32;

	/*
	 * WARNING: max_len is 5 for NFSv2.  Because of this
	 * limitation, we use the lower 16 bits of fh32[1] to hold the
	 * offset of the inode and the upper 16 bits of fh32[1] to
	 * hold the offset of the parent.
	 */
	if (parent && (len < 5)) {
		*max_len = 5;
		return FILEID_INVALID;
	} else if (len < 3) {
		*max_len = 3;
		return FILEID_INVALID;
	}

	len = 3;
	fh32[0] = ei->i_iget5_block;
 	fh16[2] = (__u16)ei->i_iget5_offset;  /* fh16 [sic] */
	fh16[3] = 0;  /* avoid leaking uninitialized data */
	fh32[2] = inode->i_generation;
	if (parent) {
		struct iso_inode_info *eparent;
		eparent = ISOFS_I(parent);
		fh32[3] = eparent->i_iget5_block;
		fh16[3] = (__u16)eparent->i_iget5_offset;  /* fh16 [sic] */
		fh32[4] = parent->i_generation;
		len = 5;
		type = 2;
	}
	*max_len = len;
	return type;
}