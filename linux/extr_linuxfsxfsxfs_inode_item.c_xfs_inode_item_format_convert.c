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
struct xfs_log_iovec {int i_len; struct xfs_inode_log_format_32* i_addr; } ;
struct xfs_inode_log_format_32 {int /*<<< orphan*/  ilf_boffset; int /*<<< orphan*/  ilf_len; int /*<<< orphan*/  ilf_blkno; int /*<<< orphan*/  ilf_u; int /*<<< orphan*/  ilf_ino; int /*<<< orphan*/  ilf_dsize; int /*<<< orphan*/  ilf_asize; int /*<<< orphan*/  ilf_fields; int /*<<< orphan*/  ilf_size; int /*<<< orphan*/  ilf_type; } ;
struct xfs_inode_log_format {int /*<<< orphan*/  ilf_boffset; int /*<<< orphan*/  ilf_len; int /*<<< orphan*/  ilf_blkno; int /*<<< orphan*/  ilf_u; int /*<<< orphan*/  ilf_ino; int /*<<< orphan*/  ilf_dsize; int /*<<< orphan*/  ilf_asize; int /*<<< orphan*/  ilf_fields; int /*<<< orphan*/  ilf_size; int /*<<< orphan*/  ilf_type; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
xfs_inode_item_format_convert(
	struct xfs_log_iovec		*buf,
	struct xfs_inode_log_format	*in_f)
{
	struct xfs_inode_log_format_32	*in_f32 = buf->i_addr;

	if (buf->i_len != sizeof(*in_f32))
		return -EFSCORRUPTED;

	in_f->ilf_type = in_f32->ilf_type;
	in_f->ilf_size = in_f32->ilf_size;
	in_f->ilf_fields = in_f32->ilf_fields;
	in_f->ilf_asize = in_f32->ilf_asize;
	in_f->ilf_dsize = in_f32->ilf_dsize;
	in_f->ilf_ino = in_f32->ilf_ino;
	memcpy(&in_f->ilf_u, &in_f32->ilf_u, sizeof(in_f->ilf_u));
	in_f->ilf_blkno = in_f32->ilf_blkno;
	in_f->ilf_len = in_f32->ilf_len;
	in_f->ilf_boffset = in_f32->ilf_boffset;
	return 0;
}