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
struct hpfs_dirent {int /*<<< orphan*/  length; scalar_t__ last; } ;
struct dnode {int /*<<< orphan*/  first_free; int /*<<< orphan*/  self; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  de_next_de (struct hpfs_dirent*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct hpfs_dirent*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hpfs_delete_de(struct super_block *s, struct dnode *d,
			   struct hpfs_dirent *de)
{
	if (de->last) {
		hpfs_error(s, "attempt to delete last dirent in dnode %08x", le32_to_cpu(d->self));
		return;
	}
	d->first_free = cpu_to_le32(le32_to_cpu(d->first_free) - le16_to_cpu(de->length));
	memmove(de, de_next_de(de), le32_to_cpu(d->first_free) + (char *)d - (char *)de);
}