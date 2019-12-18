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
struct super_block {int dummy; } ;
struct fid {int /*<<< orphan*/ * raw; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* reiserfs_get_dentry (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,int,int) ; 

struct dentry *reiserfs_fh_to_dentry(struct super_block *sb, struct fid *fid,
		int fh_len, int fh_type)
{
	/*
	 * fhtype happens to reflect the number of u32s encoded.
	 * due to a bug in earlier code, fhtype might indicate there
	 * are more u32s then actually fitted.
	 * so if fhtype seems to be more than len, reduce fhtype.
	 * Valid types are:
	 *   2 - objectid + dir_id - legacy support
	 *   3 - objectid + dir_id + generation
	 *   4 - objectid + dir_id + objectid and dirid of parent - legacy
	 *   5 - objectid + dir_id + generation + objectid and dirid of parent
	 *   6 - as above plus generation of directory
	 * 6 does not fit in NFSv2 handles
	 */
	if (fh_type > fh_len) {
		if (fh_type != 6 || fh_len != 5)
			reiserfs_warning(sb, "reiserfs-13077",
				"nfsd/reiserfs, fhtype=%d, len=%d - odd",
				fh_type, fh_len);
		fh_type = fh_len;
	}
	if (fh_len < 2)
		return NULL;

	return reiserfs_get_dentry(sb, fid->raw[0], fid->raw[1],
		(fh_type == 3 || fh_type >= 5) ? fid->raw[2] : 0);
}