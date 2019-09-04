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
struct quad_buffer_head {int dummy; } ;
struct hpfs_dirent {scalar_t__ last; } ;
struct dnode {int dummy; } ;
typedef  int /*<<< orphan*/  dnode_secno ;

/* Variables and functions */
 struct hpfs_dirent* de_next_de (struct hpfs_dirent*) ; 
 struct hpfs_dirent* dnode_end_de (struct dnode*) ; 
 struct hpfs_dirent* dnode_first_de (struct dnode*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,int /*<<< orphan*/ ,int) ; 
 struct dnode* hpfs_map_dnode (struct super_block*,int /*<<< orphan*/ ,struct quad_buffer_head*) ; 

__attribute__((used)) static struct hpfs_dirent *map_nth_dirent(struct super_block *s, dnode_secno dno, int n,
					  struct quad_buffer_head *qbh, struct dnode **dn)
{
	int i;
	struct hpfs_dirent *de, *de_end;
	struct dnode *dnode;
	dnode = hpfs_map_dnode(s, dno, qbh);
	if (!dnode) return NULL;
	if (dn) *dn=dnode;
	de = dnode_first_de(dnode);
	de_end = dnode_end_de(dnode);
	for (i = 1; de < de_end; i++, de = de_next_de(de)) {
		if (i == n) {
			return de;
		}	
		if (de->last) break;
	}
	hpfs_brelse4(qbh);
	hpfs_error(s, "map_nth_dirent: n too high; dnode = %08x, requested %08x", dno, n);
	return NULL;
}