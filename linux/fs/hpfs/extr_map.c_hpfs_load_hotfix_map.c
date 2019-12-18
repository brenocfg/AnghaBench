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
typedef  int u32 ;
struct super_block {int dummy; } ;
struct quad_buffer_head {int dummy; } ;
struct hpfs_spare_block {int /*<<< orphan*/  hotfix_map; int /*<<< orphan*/  n_spares_used; int /*<<< orphan*/  n_spares; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int n_hotfixes; void** hotfix_to; void** hotfix_from; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,...) ; 
 int /*<<< orphan*/ * hpfs_map_4sectors (struct super_block*,void*,struct quad_buffer_head*,int /*<<< orphan*/ ) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

void hpfs_load_hotfix_map(struct super_block *s, struct hpfs_spare_block *spareblock)
{
	struct quad_buffer_head qbh;
	__le32 *directory;
	u32 n_hotfixes, n_used_hotfixes;
	unsigned i;

	n_hotfixes = le32_to_cpu(spareblock->n_spares);
	n_used_hotfixes = le32_to_cpu(spareblock->n_spares_used);

	if (n_hotfixes > 256 || n_used_hotfixes > n_hotfixes) {
		hpfs_error(s, "invalid number of hotfixes: %u, used: %u", n_hotfixes, n_used_hotfixes);
		return;
	}
	if (!(directory = hpfs_map_4sectors(s, le32_to_cpu(spareblock->hotfix_map), &qbh, 0))) {
		hpfs_error(s, "can't load hotfix map");
		return;
	}
	for (i = 0; i < n_used_hotfixes; i++) {
		hpfs_sb(s)->hotfix_from[i] = le32_to_cpu(directory[i]);
		hpfs_sb(s)->hotfix_to[i] = le32_to_cpu(directory[n_hotfixes + i]);
	}
	hpfs_sb(s)->n_hotfixes = n_used_hotfixes;
	hpfs_brelse4(&qbh);
}