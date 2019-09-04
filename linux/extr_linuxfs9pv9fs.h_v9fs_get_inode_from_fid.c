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
struct v9fs_session_info {int dummy; } ;
struct super_block {int dummy; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode* v9fs_inode_from_fid (struct v9fs_session_info*,struct p9_fid*,struct super_block*,int /*<<< orphan*/ ) ; 
 struct inode* v9fs_inode_from_fid_dotl (struct v9fs_session_info*,struct p9_fid*,struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ v9fs_proto_dotl (struct v9fs_session_info*) ; 

__attribute__((used)) static inline struct inode *
v9fs_get_inode_from_fid(struct v9fs_session_info *v9ses, struct p9_fid *fid,
			struct super_block *sb)
{
	if (v9fs_proto_dotl(v9ses))
		return v9fs_inode_from_fid_dotl(v9ses, fid, sb, 0);
	else
		return v9fs_inode_from_fid(v9ses, fid, sb, 0);
}