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
struct dnode {int* dirent; void* self; void* first_free; void* magic; } ;
typedef  int /*<<< orphan*/  secno ;
typedef  int dnode_secno ;

/* Variables and functions */
 int DNODE_MAGIC ; 
 scalar_t__ FREE_DNODES_ADD ; 
 int alloc_in_dirband (struct super_block*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int hpfs_alloc_sector (struct super_block*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_free_dnode (struct super_block*,int) ; 
 struct dnode* hpfs_get_4sectors (struct super_block*,int,struct quad_buffer_head*) ; 
 scalar_t__ hpfs_get_free_dnodes (struct super_block*) ; 
 int /*<<< orphan*/  memset (struct dnode*,int /*<<< orphan*/ ,int) ; 

struct dnode *hpfs_alloc_dnode(struct super_block *s, secno near,
			 dnode_secno *dno, struct quad_buffer_head *qbh)
{
	struct dnode *d;
	if (hpfs_get_free_dnodes(s) > FREE_DNODES_ADD) {
		if (!(*dno = alloc_in_dirband(s, near)))
			if (!(*dno = hpfs_alloc_sector(s, near, 4, 0))) return NULL;
	} else {
		if (!(*dno = hpfs_alloc_sector(s, near, 4, 0)))
			if (!(*dno = alloc_in_dirband(s, near))) return NULL;
	}
	if (!(d = hpfs_get_4sectors(s, *dno, qbh))) {
		hpfs_free_dnode(s, *dno);
		return NULL;
	}
	memset(d, 0, 2048);
	d->magic = cpu_to_le32(DNODE_MAGIC);
	d->first_free = cpu_to_le32(52);
	d->dirent[0] = 32;
	d->dirent[2] = 8;
	d->dirent[30] = 1;
	d->dirent[31] = 255;
	d->self = cpu_to_le32(*dno);
	return d;
}