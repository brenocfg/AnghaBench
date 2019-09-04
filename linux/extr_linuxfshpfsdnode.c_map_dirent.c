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
struct quad_buffer_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct hpfs_dirent {scalar_t__ down; int /*<<< orphan*/  last; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct dnode {int dummy; } ;
typedef  int /*<<< orphan*/  dnode_secno ;
struct TYPE_2__ {scalar_t__ sb_chk; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de_down_pointer (struct hpfs_dirent*) ; 
 struct hpfs_dirent* de_next_de (struct hpfs_dirent*) ; 
 struct hpfs_dirent* dnode_end_de (struct dnode*) ; 
 struct hpfs_dirent* dnode_first_de (struct dnode*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int hpfs_compare_names (int /*<<< orphan*/ ,unsigned char const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_error (int /*<<< orphan*/ ,char*) ; 
 struct dnode* hpfs_map_dnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct quad_buffer_head*) ; 
 TYPE_1__* hpfs_sb (int /*<<< orphan*/ ) ; 
 scalar_t__ hpfs_stop_cycles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,char*) ; 

struct hpfs_dirent *map_dirent(struct inode *inode, dnode_secno dno,
			       const unsigned char *name, unsigned len,
			       dnode_secno *dd, struct quad_buffer_head *qbh)
{
	struct dnode *dnode;
	struct hpfs_dirent *de;
	struct hpfs_dirent *de_end;
	int c1, c2 = 0;

	if (!S_ISDIR(inode->i_mode)) hpfs_error(inode->i_sb, "map_dirent: not a directory\n");
	again:
	if (hpfs_sb(inode->i_sb)->sb_chk)
		if (hpfs_stop_cycles(inode->i_sb, dno, &c1, &c2, "map_dirent")) return NULL;
	if (!(dnode = hpfs_map_dnode(inode->i_sb, dno, qbh))) return NULL;
	
	de_end = dnode_end_de(dnode);
	for (de = dnode_first_de(dnode); de < de_end; de = de_next_de(de)) {
		int t = hpfs_compare_names(inode->i_sb, name, len, de->name, de->namelen, de->last);
		if (!t) {
			if (dd) *dd = dno;
			return de;
		}
		if (t < 0) {
			if (de->down) {
				dno = de_down_pointer(de);
				hpfs_brelse4(qbh);
				goto again;
			}
		break;
		}
	}
	hpfs_brelse4(qbh);
	return NULL;
}