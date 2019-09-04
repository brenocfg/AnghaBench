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
struct ubifs_sb_node {int /*<<< orphan*/  flags; } ;
struct ubifs_info {int space_fixup; int /*<<< orphan*/  ro_mount; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_sb_node*) ; 
 int PTR_ERR (struct ubifs_sb_node*) ; 
 int /*<<< orphan*/  UBIFS_FLG_SPACE_FIXUP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int fixup_free_space (struct ubifs_info*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_sb_node*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_msg (struct ubifs_info*,char*) ; 
 struct ubifs_sb_node* ubifs_read_sb_node (struct ubifs_info*) ; 
 int ubifs_write_sb_node (struct ubifs_info*,struct ubifs_sb_node*) ; 

int ubifs_fixup_free_space(struct ubifs_info *c)
{
	int err;
	struct ubifs_sb_node *sup;

	ubifs_assert(c, c->space_fixup);
	ubifs_assert(c, !c->ro_mount);

	ubifs_msg(c, "start fixing up free space");

	err = fixup_free_space(c);
	if (err)
		return err;

	sup = ubifs_read_sb_node(c);
	if (IS_ERR(sup))
		return PTR_ERR(sup);

	/* Free-space fixup is no longer required */
	c->space_fixup = 0;
	sup->flags &= cpu_to_le32(~UBIFS_FLG_SPACE_FIXUP);

	err = ubifs_write_sb_node(c, sup);
	kfree(sup);
	if (err)
		return err;

	ubifs_msg(c, "free space fixup complete");
	return err;
}