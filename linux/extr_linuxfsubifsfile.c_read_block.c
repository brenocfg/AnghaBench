#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  sqnum; } ;
struct ubifs_data_node {int /*<<< orphan*/  compr_type; int /*<<< orphan*/  data; TYPE_2__ ch; int /*<<< orphan*/  size; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_6__ {scalar_t__ creat_sqnum; } ;
struct TYPE_4__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int UBIFS_BLOCK_SIZE ; 
 void* UBIFS_DATA_NODE_SZ ; 
 int /*<<< orphan*/  data_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 scalar_t__ ubifs_crypt_is_encrypted (struct inode*) ; 
 int ubifs_decompress (struct ubifs_info*,int /*<<< orphan*/ *,unsigned int,void*,int*,int /*<<< orphan*/ ) ; 
 int ubifs_decrypt (struct inode*,struct ubifs_data_node*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,struct ubifs_data_node*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_3__* ubifs_inode (struct inode*) ; 
 int ubifs_tnc_lookup (struct ubifs_info*,union ubifs_key*,struct ubifs_data_node*) ; 

__attribute__((used)) static int read_block(struct inode *inode, void *addr, unsigned int block,
		      struct ubifs_data_node *dn)
{
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	int err, len, out_len;
	union ubifs_key key;
	unsigned int dlen;

	data_key_init(c, &key, inode->i_ino, block);
	err = ubifs_tnc_lookup(c, &key, dn);
	if (err) {
		if (err == -ENOENT)
			/* Not found, so it must be a hole */
			memset(addr, 0, UBIFS_BLOCK_SIZE);
		return err;
	}

	ubifs_assert(c, le64_to_cpu(dn->ch.sqnum) >
		     ubifs_inode(inode)->creat_sqnum);
	len = le32_to_cpu(dn->size);
	if (len <= 0 || len > UBIFS_BLOCK_SIZE)
		goto dump;

	dlen = le32_to_cpu(dn->ch.len) - UBIFS_DATA_NODE_SZ;

	if (ubifs_crypt_is_encrypted(inode)) {
		err = ubifs_decrypt(inode, dn, &dlen, block);
		if (err)
			goto dump;
	}

	out_len = UBIFS_BLOCK_SIZE;
	err = ubifs_decompress(c, &dn->data, dlen, addr, &out_len,
			       le16_to_cpu(dn->compr_type));
	if (err || len != out_len)
		goto dump;

	/*
	 * Data length can be less than a full block, even for blocks that are
	 * not the last in the file (e.g., as a result of making a hole and
	 * appending data). Ensure that the remainder is zeroed out.
	 */
	if (len < UBIFS_BLOCK_SIZE)
		memset(addr + len, 0, UBIFS_BLOCK_SIZE - len);

	return 0;

dump:
	ubifs_err(c, "bad data node (block %u, inode %lu)",
		  block, inode->i_ino);
	ubifs_dump_node(c, dn);
	return -EINVAL;
}