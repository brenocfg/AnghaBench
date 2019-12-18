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
struct ocfs2_super {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_dir_indexed (struct inode*) ; 
 scalar_t__ ocfs2_meta_ecc (struct ocfs2_super*) ; 

__attribute__((used)) static int ocfs2_supports_dir_trailer(struct inode *dir)
{
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);

	if (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		return 0;

	return ocfs2_meta_ecc(osb) || ocfs2_dir_indexed(dir);
}