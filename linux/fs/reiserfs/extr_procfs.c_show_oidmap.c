#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct seq_file {struct super_block* private; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_oid_maxsize; int /*<<< orphan*/  s_oid_cursize; } ;
struct reiserfs_super_block {TYPE_2__ s_v1; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mapf; scalar_t__ use_file; } ;
struct reiserfs_sb_info {TYPE_1__ oidmap; struct reiserfs_super_block* s_rs; } ;
typedef  int /*<<< orphan*/  reiserfs_oidinterval_d_t ;
typedef  int loff_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_6__ {int i_size; } ;

/* Variables and functions */
 scalar_t__ MAP (int) ; 
 scalar_t__ MAX_KEY_OBJECTID ; 
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 TYPE_3__* file_inode (int /*<<< orphan*/ *) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int show_oidmap(struct seq_file *m, void *unused)
{
	struct super_block *sb = m->private;
	struct reiserfs_sb_info *sb_info = REISERFS_SB(sb);
	struct reiserfs_super_block *rs = sb_info->s_rs;
	unsigned int mapsize = le16_to_cpu(rs->s_v1.s_oid_cursize);
	unsigned long total_used = 0;
	int i;

	for (i = 0; i < mapsize; ++i) {
		__u32 right;

		right = (i == mapsize - 1) ? MAX_KEY_OBJECTID : MAP(i + 1);
		seq_printf(m, "%s: [ %x .. %x )\n",
			   (i & 1) ? "free" : "used", MAP(i), right);
		if (!(i & 1)) {
			total_used += right - MAP(i);
		}
	}
#if defined( REISERFS_USE_OIDMAPF )
	if (sb_info->oidmap.use_file && (sb_info->oidmap.mapf != NULL)) {
		loff_t size = file_inode(sb_info->oidmap.mapf)->i_size;
		total_used += size / sizeof(reiserfs_oidinterval_d_t);
	}
#endif
	seq_printf(m, "total: \t%i [%i/%i] used: %lu [exact]\n",
		   mapsize,
		   mapsize, le16_to_cpu(rs->s_v1.s_oid_maxsize), total_used);
	return 0;
}