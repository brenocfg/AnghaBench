#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_wbuf {int dummy; } ;
struct ubifs_info {TYPE_2__* jheads; } ;
struct TYPE_5__ {void* node_type; } ;
struct ubifs_dent_node {char* name; void* nlen; void* type; void* inum; int /*<<< orphan*/  key; TYPE_1__ ch; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct fscrypt_name {int dummy; } ;
struct TYPE_7__ {scalar_t__ data_len; int /*<<< orphan*/  ui_mutex; } ;
struct TYPE_6__ {struct ubifs_wbuf wbuf; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 size_t BASEHD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 void* UBIFS_DENT_NODE ; 
 int UBIFS_DENT_NODE_SZ ; 
 int UBIFS_INO_NODE_SZ ; 
 void* cpu_to_le16 (size_t) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dent_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ,struct fscrypt_name const*) ; 
 int /*<<< orphan*/  dent_key_init_flash (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fscrypt_name const*) ; 
 int /*<<< orphan*/  finish_reservation (struct ubifs_info*) ; 
 size_t fname_len (struct fscrypt_name const*) ; 
 int /*<<< orphan*/  fname_name (struct fscrypt_name const*) ; 
 void* get_dent_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 struct ubifs_dent_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int make_reservation (struct ubifs_info*,size_t,int) ; 
 int /*<<< orphan*/  mark_inode_clean (struct ubifs_info*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_inode (struct ubifs_info*,void*,struct inode const*,int) ; 
 int /*<<< orphan*/  release_head (struct ubifs_info*,size_t) ; 
 int /*<<< orphan*/  set_dent_cookie (struct ubifs_info*,struct ubifs_dent_node*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 TYPE_3__* ubifs_inode (struct inode const*) ; 
 int /*<<< orphan*/  ubifs_prep_grp_node (struct ubifs_info*,struct ubifs_dent_node*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_tnc_add (struct ubifs_info*,union ubifs_key*,int,int,int) ; 
 int ubifs_tnc_add_nm (struct ubifs_info*,union ubifs_key*,int,int,int,struct fscrypt_name const*) ; 
 int /*<<< orphan*/  ubifs_wbuf_add_ino_nolock (struct ubifs_wbuf*,int /*<<< orphan*/ ) ; 
 int write_head (struct ubifs_info*,size_t,struct ubifs_dent_node*,int,int*,int*,int) ; 
 int /*<<< orphan*/  zero_dent_node_unused (struct ubifs_dent_node*) ; 

int ubifs_jnl_xrename(struct ubifs_info *c, const struct inode *fst_dir,
		      const struct inode *fst_inode,
		      const struct fscrypt_name *fst_nm,
		      const struct inode *snd_dir,
		      const struct inode *snd_inode,
		      const struct fscrypt_name *snd_nm, int sync)
{
	union ubifs_key key;
	struct ubifs_dent_node *dent1, *dent2;
	int err, dlen1, dlen2, lnum, offs, len, plen = UBIFS_INO_NODE_SZ;
	int aligned_dlen1, aligned_dlen2;
	int twoparents = (fst_dir != snd_dir);
	void *p;

	ubifs_assert(c, ubifs_inode(fst_dir)->data_len == 0);
	ubifs_assert(c, ubifs_inode(snd_dir)->data_len == 0);
	ubifs_assert(c, mutex_is_locked(&ubifs_inode(fst_dir)->ui_mutex));
	ubifs_assert(c, mutex_is_locked(&ubifs_inode(snd_dir)->ui_mutex));

	dlen1 = UBIFS_DENT_NODE_SZ + fname_len(snd_nm) + 1;
	dlen2 = UBIFS_DENT_NODE_SZ + fname_len(fst_nm) + 1;
	aligned_dlen1 = ALIGN(dlen1, 8);
	aligned_dlen2 = ALIGN(dlen2, 8);

	len = aligned_dlen1 + aligned_dlen2 + ALIGN(plen, 8);
	if (twoparents)
		len += plen;

	dent1 = kzalloc(len, GFP_NOFS);
	if (!dent1)
		return -ENOMEM;

	/* Make reservation before allocating sequence numbers */
	err = make_reservation(c, BASEHD, len);
	if (err)
		goto out_free;

	/* Make new dent for 1st entry */
	dent1->ch.node_type = UBIFS_DENT_NODE;
	dent_key_init_flash(c, &dent1->key, snd_dir->i_ino, snd_nm);
	dent1->inum = cpu_to_le64(fst_inode->i_ino);
	dent1->type = get_dent_type(fst_inode->i_mode);
	dent1->nlen = cpu_to_le16(fname_len(snd_nm));
	memcpy(dent1->name, fname_name(snd_nm), fname_len(snd_nm));
	dent1->name[fname_len(snd_nm)] = '\0';
	set_dent_cookie(c, dent1);
	zero_dent_node_unused(dent1);
	ubifs_prep_grp_node(c, dent1, dlen1, 0);

	/* Make new dent for 2nd entry */
	dent2 = (void *)dent1 + aligned_dlen1;
	dent2->ch.node_type = UBIFS_DENT_NODE;
	dent_key_init_flash(c, &dent2->key, fst_dir->i_ino, fst_nm);
	dent2->inum = cpu_to_le64(snd_inode->i_ino);
	dent2->type = get_dent_type(snd_inode->i_mode);
	dent2->nlen = cpu_to_le16(fname_len(fst_nm));
	memcpy(dent2->name, fname_name(fst_nm), fname_len(fst_nm));
	dent2->name[fname_len(fst_nm)] = '\0';
	set_dent_cookie(c, dent2);
	zero_dent_node_unused(dent2);
	ubifs_prep_grp_node(c, dent2, dlen2, 0);

	p = (void *)dent2 + aligned_dlen2;
	if (!twoparents)
		pack_inode(c, p, fst_dir, 1);
	else {
		pack_inode(c, p, fst_dir, 0);
		p += ALIGN(plen, 8);
		pack_inode(c, p, snd_dir, 1);
	}

	err = write_head(c, BASEHD, dent1, len, &lnum, &offs, sync);
	if (err)
		goto out_release;
	if (!sync) {
		struct ubifs_wbuf *wbuf = &c->jheads[BASEHD].wbuf;

		ubifs_wbuf_add_ino_nolock(wbuf, fst_dir->i_ino);
		ubifs_wbuf_add_ino_nolock(wbuf, snd_dir->i_ino);
	}
	release_head(c, BASEHD);

	dent_key_init(c, &key, snd_dir->i_ino, snd_nm);
	err = ubifs_tnc_add_nm(c, &key, lnum, offs, dlen1, snd_nm);
	if (err)
		goto out_ro;

	offs += aligned_dlen1;
	dent_key_init(c, &key, fst_dir->i_ino, fst_nm);
	err = ubifs_tnc_add_nm(c, &key, lnum, offs, dlen2, fst_nm);
	if (err)
		goto out_ro;

	offs += aligned_dlen2;

	ino_key_init(c, &key, fst_dir->i_ino);
	err = ubifs_tnc_add(c, &key, lnum, offs, plen);
	if (err)
		goto out_ro;

	if (twoparents) {
		offs += ALIGN(plen, 8);
		ino_key_init(c, &key, snd_dir->i_ino);
		err = ubifs_tnc_add(c, &key, lnum, offs, plen);
		if (err)
			goto out_ro;
	}

	finish_reservation(c);

	mark_inode_clean(c, ubifs_inode(fst_dir));
	if (twoparents)
		mark_inode_clean(c, ubifs_inode(snd_dir));
	kfree(dent1);
	return 0;

out_release:
	release_head(c, BASEHD);
out_ro:
	ubifs_ro_mode(c, err);
	finish_reservation(c);
out_free:
	kfree(dent1);
	return err;
}