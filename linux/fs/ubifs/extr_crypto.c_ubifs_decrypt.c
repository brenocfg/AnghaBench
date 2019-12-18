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
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int UBIFS_BLOCK_SIZE ; 
 int fscrypt_decrypt_block_inplace (struct inode const*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

int ubifs_decrypt(const struct inode *inode, struct ubifs_data_node *dn,
		  unsigned int *out_len, int block)
{
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	int err;
	unsigned int clen = le16_to_cpu(dn->compr_size);
	unsigned int dlen = *out_len;

	if (clen <= 0 || clen > UBIFS_BLOCK_SIZE || clen > dlen) {
		ubifs_err(c, "bad compr_size: %i", clen);
		return -EINVAL;
	}

	ubifs_assert(c, dlen <= UBIFS_BLOCK_SIZE);
	err = fscrypt_decrypt_block_inplace(inode, virt_to_page(&dn->data),
					    dlen, offset_in_page(&dn->data),
					    block);
	if (err) {
		ubifs_err(c, "fscrypt_decrypt_block_inplace() failed: %d", err);
		return err;
	}
	*out_len = clen;

	return 0;
}