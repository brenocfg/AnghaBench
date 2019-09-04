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
struct ubifs_info {int dummy; } ;
struct ubifs_data_node {int /*<<< orphan*/  data; int /*<<< orphan*/  compr_size; } ;
struct page {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  UBIFS_CIPHER_BLOCK_SIZE ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 struct page* fscrypt_encrypt_page (struct inode const*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ *) ; 
 unsigned int round_up (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

int ubifs_encrypt(const struct inode *inode, struct ubifs_data_node *dn,
		  unsigned int in_len, unsigned int *out_len, int block)
{
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	void *p = &dn->data;
	struct page *ret;
	unsigned int pad_len = round_up(in_len, UBIFS_CIPHER_BLOCK_SIZE);

	ubifs_assert(c, pad_len <= *out_len);
	dn->compr_size = cpu_to_le16(in_len);

	/* pad to full block cipher length */
	if (pad_len != in_len)
		memset(p + in_len, 0, pad_len - in_len);

	ret = fscrypt_encrypt_page(inode, virt_to_page(&dn->data), pad_len,
			offset_in_page(&dn->data), block, GFP_NOFS);
	if (IS_ERR(ret)) {
		ubifs_err(c, "fscrypt_encrypt_page failed: %ld", PTR_ERR(ret));
		return PTR_ERR(ret);
	}
	*out_len = pad_len;

	return 0;
}