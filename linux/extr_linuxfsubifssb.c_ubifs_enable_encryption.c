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
struct ubifs_info {int encrypted; int fmt_version; scalar_t__ ro_media; scalar_t__ ro_mount; } ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 scalar_t__ IS_ERR (struct ubifs_sb_node*) ; 
 int PTR_ERR (struct ubifs_sb_node*) ; 
 int /*<<< orphan*/  UBIFS_FLG_ENCRYPTION ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ubifs_sb_node*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*) ; 
 struct ubifs_sb_node* ubifs_read_sb_node (struct ubifs_info*) ; 
 int ubifs_write_sb_node (struct ubifs_info*,struct ubifs_sb_node*) ; 

int ubifs_enable_encryption(struct ubifs_info *c)
{
	int err;
	struct ubifs_sb_node *sup;

	if (c->encrypted)
		return 0;

	if (c->ro_mount || c->ro_media)
		return -EROFS;

	if (c->fmt_version < 5) {
		ubifs_err(c, "on-flash format version 5 is needed for encryption");
		return -EINVAL;
	}

	sup = ubifs_read_sb_node(c);
	if (IS_ERR(sup))
		return PTR_ERR(sup);

	sup->flags |= cpu_to_le32(UBIFS_FLG_ENCRYPTION);

	err = ubifs_write_sb_node(c, sup);
	if (!err)
		c->encrypted = 1;
	kfree(sup);

	return err;
}