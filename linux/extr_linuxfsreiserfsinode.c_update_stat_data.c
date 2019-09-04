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
struct treepath {int dummy; } ;
struct item_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_PKEY (struct inode*) ; 
 struct buffer_head* PATH_PLAST_BUFFER (struct treepath*) ; 
 int /*<<< orphan*/  ih_item_body (struct buffer_head*,struct item_head*) ; 
 int /*<<< orphan*/  inode2sd (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode2sd_v1 (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_statdata_le_ih (struct item_head*) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,struct item_head*) ; 
 scalar_t__ stat_data_v1 (struct item_head*) ; 
 struct item_head* tp_item_head (struct treepath*) ; 

__attribute__((used)) static void update_stat_data(struct treepath *path, struct inode *inode,
			     loff_t size)
{
	struct buffer_head *bh;
	struct item_head *ih;

	bh = PATH_PLAST_BUFFER(path);
	ih = tp_item_head(path);

	if (!is_statdata_le_ih(ih))
		reiserfs_panic(inode->i_sb, "vs-13065", "key %k, found item %h",
			       INODE_PKEY(inode), ih);

	/* path points to old stat data */
	if (stat_data_v1(ih)) {
		inode2sd_v1(ih_item_body(bh, ih), inode, size);
	} else {
		inode2sd(ih_item_body(bh, ih), inode, size);
	}

	return;
}