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
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ino; } ;
struct fid {TYPE_1__ i32; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int FILEID_INO32_GEN ; 
 int FILEID_INO32_GEN_PARENT ; 
 struct dentry* squashfs_export_iget (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *squashfs_fh_to_dentry(struct super_block *sb,
		struct fid *fid, int fh_len, int fh_type)
{
	if ((fh_type != FILEID_INO32_GEN && fh_type != FILEID_INO32_GEN_PARENT)
			|| fh_len < 2)
		return NULL;

	return squashfs_export_iget(sb, fid->i32.ino);
}