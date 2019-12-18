#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_mapping; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
struct TYPE_4__ {void* i_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 char const* ERR_CAST (struct page*) ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_2__* EXT4_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ ext4_inode_is_fast_symlink (struct inode*) ; 
 char* fscrypt_get_symlink (struct inode*,void const*,unsigned int,struct delayed_call*) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *ext4_encrypted_get_link(struct dentry *dentry,
					   struct inode *inode,
					   struct delayed_call *done)
{
	struct page *cpage = NULL;
	const void *caddr;
	unsigned int max_size;
	const char *paddr;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	if (ext4_inode_is_fast_symlink(inode)) {
		caddr = EXT4_I(inode)->i_data;
		max_size = sizeof(EXT4_I(inode)->i_data);
	} else {
		cpage = read_mapping_page(inode->i_mapping, 0, NULL);
		if (IS_ERR(cpage))
			return ERR_CAST(cpage);
		caddr = page_address(cpage);
		max_size = inode->i_sb->s_blocksize;
	}

	paddr = fscrypt_get_symlink(inode, caddr, max_size, done);
	if (cpage)
		put_page(cpage);
	return paddr;
}