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
struct hpfs_dirent {int down; int /*<<< orphan*/  length; } ;
struct dnode {int /*<<< orphan*/  first_free; int /*<<< orphan*/  self; } ;
typedef  scalar_t__ dnode_secno ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {scalar_t__ sb_chk; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  de_down_pointer (struct hpfs_dirent*) ; 
 struct hpfs_dirent* dnode_last_de (struct dnode*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,int,...) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_last_pointer(struct super_block *s, struct dnode *d, dnode_secno ptr)
{
	struct hpfs_dirent *de;
	if (!(de = dnode_last_de(d))) {
		hpfs_error(s, "set_last_pointer: empty dnode %08x", le32_to_cpu(d->self));
		return;
	}
	if (hpfs_sb(s)->sb_chk) {
		if (de->down) {
			hpfs_error(s, "set_last_pointer: dnode %08x has already last pointer %08x",
				le32_to_cpu(d->self), de_down_pointer(de));
			return;
		}
		if (le16_to_cpu(de->length) != 32) {
			hpfs_error(s, "set_last_pointer: bad last dirent in dnode %08x", le32_to_cpu(d->self));
			return;
		}
	}
	if (ptr) {
		le32_add_cpu(&d->first_free, 4);
		if (le32_to_cpu(d->first_free) > 2048) {
			hpfs_error(s, "set_last_pointer: too long dnode %08x", le32_to_cpu(d->self));
			le32_add_cpu(&d->first_free, -4);
			return;
		}
		de->length = cpu_to_le16(36);
		de->down = 1;
		*(__le32 *)((char *)de + 32) = cpu_to_le32(ptr);
	}
}