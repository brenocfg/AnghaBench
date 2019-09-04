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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct inode {TYPE_2__* i_sb; } ;
struct TYPE_4__ {TYPE_1__* s_cop; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FS_CFLG_OWN_PAGES ; 
 int /*<<< orphan*/  FS_DECRYPT ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int fscrypt_do_page_crypto (struct inode const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*,struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int fscrypt_decrypt_page(const struct inode *inode, struct page *page,
			unsigned int len, unsigned int offs, u64 lblk_num)
{
	if (!(inode->i_sb->s_cop->flags & FS_CFLG_OWN_PAGES))
		BUG_ON(!PageLocked(page));

	return fscrypt_do_page_crypto(inode, FS_DECRYPT, lblk_num, page, page,
				      len, offs, GFP_NOFS);
}