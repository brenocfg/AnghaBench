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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_DECRYPT ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int fscrypt_crypt_block (struct inode const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*,struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int fscrypt_decrypt_block_inplace(const struct inode *inode, struct page *page,
				  unsigned int len, unsigned int offs,
				  u64 lblk_num)
{
	return fscrypt_crypt_block(inode, FS_DECRYPT, lblk_num, page, page,
				   len, offs, GFP_NOFS);
}