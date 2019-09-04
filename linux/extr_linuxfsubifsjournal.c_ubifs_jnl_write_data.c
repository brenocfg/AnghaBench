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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_inode {int flags; int compr_type; } ;
struct ubifs_info {int /*<<< orphan*/  write_reserve_mutex; TYPE_2__* jheads; struct ubifs_data_node* write_reserve_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  node_type; } ;
struct ubifs_data_node {int /*<<< orphan*/  compr_type; scalar_t__ compr_size; int /*<<< orphan*/  data; int /*<<< orphan*/  size; int /*<<< orphan*/  key; TYPE_1__ ch; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  wbuf; } ;

/* Variables and functions */
 int COMPRESSED_DATA_NODE_BUF_SZ ; 
 size_t DATAHD ; 
 int GFP_NOFS ; 
 int UBIFS_BLOCK_SIZE ; 
 scalar_t__ UBIFS_CIPHER_BLOCK_SIZE ; 
 int UBIFS_COMPR_FL ; 
 int UBIFS_COMPR_NONE ; 
 int /*<<< orphan*/  UBIFS_DATA_NODE ; 
 int UBIFS_DATA_NODE_SZ ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dbg_jnlk (union ubifs_key const*,char*,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  finish_reservation (struct ubifs_info*) ; 
 int /*<<< orphan*/  key_block (struct ubifs_info*,union ubifs_key const*) ; 
 scalar_t__ key_inum (struct ubifs_info*,union ubifs_key const*) ; 
 int /*<<< orphan*/  key_write (struct ubifs_info*,union ubifs_key const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ubifs_data_node*) ; 
 struct ubifs_data_node* kmalloc (int,int) ; 
 int make_reservation (struct ubifs_info*,size_t,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_head (struct ubifs_info*,size_t) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_compress (struct ubifs_info*,void const*,int,int /*<<< orphan*/ *,int*,int*) ; 
 int ubifs_crypt_is_encrypted (struct inode const*) ; 
 int ubifs_encrypt (struct inode const*,struct ubifs_data_node*,int,int*,int /*<<< orphan*/ ) ; 
 struct ubifs_inode* ubifs_inode (struct inode const*) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_tnc_add (struct ubifs_info*,union ubifs_key const*,int,int,int) ; 
 int /*<<< orphan*/  ubifs_wbuf_add_ino_nolock (int /*<<< orphan*/ *,scalar_t__) ; 
 int write_node (struct ubifs_info*,size_t,struct ubifs_data_node*,int,int*,int*) ; 

int ubifs_jnl_write_data(struct ubifs_info *c, const struct inode *inode,
			 const union ubifs_key *key, const void *buf, int len)
{
	struct ubifs_data_node *data;
	int err, lnum, offs, compr_type, out_len, compr_len;
	int dlen = COMPRESSED_DATA_NODE_BUF_SZ, allocated = 1;
	struct ubifs_inode *ui = ubifs_inode(inode);
	bool encrypted = ubifs_crypt_is_encrypted(inode);

	dbg_jnlk(key, "ino %lu, blk %u, len %d, key ",
		(unsigned long)key_inum(c, key), key_block(c, key), len);
	ubifs_assert(c, len <= UBIFS_BLOCK_SIZE);

	if (encrypted)
		dlen += UBIFS_CIPHER_BLOCK_SIZE;

	data = kmalloc(dlen, GFP_NOFS | __GFP_NOWARN);
	if (!data) {
		/*
		 * Fall-back to the write reserve buffer. Note, we might be
		 * currently on the memory reclaim path, when the kernel is
		 * trying to free some memory by writing out dirty pages. The
		 * write reserve buffer helps us to guarantee that we are
		 * always able to write the data.
		 */
		allocated = 0;
		mutex_lock(&c->write_reserve_mutex);
		data = c->write_reserve_buf;
	}

	data->ch.node_type = UBIFS_DATA_NODE;
	key_write(c, key, &data->key);
	data->size = cpu_to_le32(len);

	if (!(ui->flags & UBIFS_COMPR_FL))
		/* Compression is disabled for this inode */
		compr_type = UBIFS_COMPR_NONE;
	else
		compr_type = ui->compr_type;

	out_len = compr_len = dlen - UBIFS_DATA_NODE_SZ;
	ubifs_compress(c, buf, len, &data->data, &compr_len, &compr_type);
	ubifs_assert(c, compr_len <= UBIFS_BLOCK_SIZE);

	if (encrypted) {
		err = ubifs_encrypt(inode, data, compr_len, &out_len, key_block(c, key));
		if (err)
			goto out_free;

	} else {
		data->compr_size = 0;
		out_len = compr_len;
	}

	dlen = UBIFS_DATA_NODE_SZ + out_len;
	data->compr_type = cpu_to_le16(compr_type);

	/* Make reservation before allocating sequence numbers */
	err = make_reservation(c, DATAHD, dlen);
	if (err)
		goto out_free;

	err = write_node(c, DATAHD, data, dlen, &lnum, &offs);
	if (err)
		goto out_release;
	ubifs_wbuf_add_ino_nolock(&c->jheads[DATAHD].wbuf, key_inum(c, key));
	release_head(c, DATAHD);

	err = ubifs_tnc_add(c, key, lnum, offs, dlen);
	if (err)
		goto out_ro;

	finish_reservation(c);
	if (!allocated)
		mutex_unlock(&c->write_reserve_mutex);
	else
		kfree(data);
	return 0;

out_release:
	release_head(c, DATAHD);
out_ro:
	ubifs_ro_mode(c, err);
	finish_reservation(c);
out_free:
	if (!allocated)
		mutex_unlock(&c->write_reserve_mutex);
	else
		kfree(data);
	return err;
}