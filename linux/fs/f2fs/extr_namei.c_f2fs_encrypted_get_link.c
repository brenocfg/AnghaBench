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
struct page {int dummy; } ;
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_mapping; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 char const* ERR_CAST (struct page*) ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 char* fscrypt_get_symlink (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct delayed_call*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *f2fs_encrypted_get_link(struct dentry *dentry,
					   struct inode *inode,
					   struct delayed_call *done)
{
	struct page *page;
	const char *target;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	page = read_mapping_page(inode->i_mapping, 0, NULL);
	if (IS_ERR(page))
		return ERR_CAST(page);

	target = fscrypt_get_symlink(inode, page_address(page),
				     inode->i_sb->s_blocksize, done);
	put_page(page);
	return target;
}