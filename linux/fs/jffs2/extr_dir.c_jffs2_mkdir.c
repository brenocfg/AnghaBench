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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct jffs2_unknown_node {int dummy; } ;
struct jffs2_sb_info {int dummy; } ;
struct jffs2_raw_inode {int nsize; void* mctime; void* name_crc; void* node_crc; int /*<<< orphan*/  type; void* ino; void* version; void* pino; void* hdr_crc; void* totlen; void* nodetype; void* magic; void* data_crc; } ;
struct jffs2_raw_dirent {int nsize; void* mctime; void* name_crc; void* node_crc; int /*<<< orphan*/  type; void* ino; void* version; void* pino; void* hdr_crc; void* totlen; void* nodetype; void* magic; void* data_crc; } ;
struct jffs2_inode_info {int highest_version; int /*<<< orphan*/  sem; int /*<<< orphan*/  dents; struct jffs2_full_dnode* metadata; TYPE_1__* inocache; } ;
struct jffs2_full_dnode {int i_ino; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_sb; } ;
struct jffs2_full_dirent {int i_ino; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_sb; } ;
struct inode {int i_ino; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {int len; struct jffs2_raw_inode* name; } ;
struct dentry {TYPE_2__ d_name; } ;
struct TYPE_3__ {int pino_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_NORMAL ; 
 int /*<<< orphan*/  DT_DIR ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct jffs2_full_dnode*) ; 
 int /*<<< orphan*/  ITIME (int /*<<< orphan*/ ) ; 
 struct jffs2_inode_info* JFFS2_INODE_INFO (struct jffs2_full_dnode*) ; 
 int /*<<< orphan*/  JFFS2_MAGIC_BITMASK ; 
 int /*<<< orphan*/  JFFS2_NODETYPE_DIRENT ; 
 int JFFS2_NOW () ; 
 struct jffs2_sb_info* JFFS2_SB_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_DIRENT_SIZE (int) ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_INODE_SIZE ; 
 int PTR_ERR (struct jffs2_full_dnode*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 void* cpu_to_je16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_je32 (int) ; 
 int crc32 (int /*<<< orphan*/ ,struct jffs2_raw_inode*,int) ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct jffs2_full_dnode*) ; 
 int /*<<< orphan*/  iget_failed (struct jffs2_full_dnode*) ; 
 int /*<<< orphan*/  inc_nlink (struct jffs2_full_dnode*) ; 
 int /*<<< orphan*/  je32_to_cpu (void*) ; 
 int /*<<< orphan*/  jffs2_add_fd_to_list (struct jffs2_sb_info*,struct jffs2_full_dnode*,int /*<<< orphan*/ *) ; 
 struct jffs2_raw_inode* jffs2_alloc_raw_dirent () ; 
 struct jffs2_raw_inode* jffs2_alloc_raw_inode () ; 
 int /*<<< orphan*/  jffs2_complete_reservation (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_dir_inode_operations ; 
 int /*<<< orphan*/  jffs2_dir_operations ; 
 int /*<<< orphan*/  jffs2_free_raw_dirent (struct jffs2_raw_inode*) ; 
 int /*<<< orphan*/  jffs2_free_raw_inode (struct jffs2_raw_inode*) ; 
 int jffs2_init_acl_post (struct jffs2_full_dnode*) ; 
 int jffs2_init_security (struct jffs2_full_dnode*,struct jffs2_full_dnode*,TYPE_2__*) ; 
 struct jffs2_full_dnode* jffs2_new_inode (struct jffs2_full_dnode*,int /*<<< orphan*/ ,struct jffs2_raw_inode*) ; 
 int jffs2_reserve_space (struct jffs2_sb_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jffs2_full_dnode* jffs2_write_dirent (struct jffs2_sb_info*,struct jffs2_inode_info*,struct jffs2_raw_inode*,struct jffs2_raw_inode*,int,int /*<<< orphan*/ ) ; 
 struct jffs2_full_dnode* jffs2_write_dnode (struct jffs2_sb_info*,struct jffs2_inode_info*,struct jffs2_raw_inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_nlink (struct jffs2_full_dnode*,int) ; 

__attribute__((used)) static int jffs2_mkdir (struct inode *dir_i, struct dentry *dentry, umode_t mode)
{
	struct jffs2_inode_info *f, *dir_f;
	struct jffs2_sb_info *c;
	struct inode *inode;
	struct jffs2_raw_inode *ri;
	struct jffs2_raw_dirent *rd;
	struct jffs2_full_dnode *fn;
	struct jffs2_full_dirent *fd;
	int namelen;
	uint32_t alloclen;
	int ret;

	mode |= S_IFDIR;

	ri = jffs2_alloc_raw_inode();
	if (!ri)
		return -ENOMEM;

	c = JFFS2_SB_INFO(dir_i->i_sb);

	/* Try to reserve enough space for both node and dirent.
	 * Just the node will do for now, though
	 */
	namelen = dentry->d_name.len;
	ret = jffs2_reserve_space(c, sizeof(*ri), &alloclen, ALLOC_NORMAL,
				  JFFS2_SUMMARY_INODE_SIZE);

	if (ret) {
		jffs2_free_raw_inode(ri);
		return ret;
	}

	inode = jffs2_new_inode(dir_i, mode, ri);

	if (IS_ERR(inode)) {
		jffs2_free_raw_inode(ri);
		jffs2_complete_reservation(c);
		return PTR_ERR(inode);
	}

	inode->i_op = &jffs2_dir_inode_operations;
	inode->i_fop = &jffs2_dir_operations;

	f = JFFS2_INODE_INFO(inode);

	/* Directories get nlink 2 at start */
	set_nlink(inode, 2);
	/* but ic->pino_nlink is the parent ino# */
	f->inocache->pino_nlink = dir_i->i_ino;

	ri->data_crc = cpu_to_je32(0);
	ri->node_crc = cpu_to_je32(crc32(0, ri, sizeof(*ri)-8));

	fn = jffs2_write_dnode(c, f, ri, NULL, 0, ALLOC_NORMAL);

	jffs2_free_raw_inode(ri);

	if (IS_ERR(fn)) {
		/* Eeek. Wave bye bye */
		mutex_unlock(&f->sem);
		jffs2_complete_reservation(c);
		ret = PTR_ERR(fn);
		goto fail;
	}
	/* No data here. Only a metadata node, which will be
	   obsoleted by the first data write
	*/
	f->metadata = fn;
	mutex_unlock(&f->sem);

	jffs2_complete_reservation(c);

	ret = jffs2_init_security(inode, dir_i, &dentry->d_name);
	if (ret)
		goto fail;

	ret = jffs2_init_acl_post(inode);
	if (ret)
		goto fail;

	ret = jffs2_reserve_space(c, sizeof(*rd)+namelen, &alloclen,
				  ALLOC_NORMAL, JFFS2_SUMMARY_DIRENT_SIZE(namelen));
	if (ret)
		goto fail;

	rd = jffs2_alloc_raw_dirent();
	if (!rd) {
		/* Argh. Now we treat it like a normal delete */
		jffs2_complete_reservation(c);
		ret = -ENOMEM;
		goto fail;
	}

	dir_f = JFFS2_INODE_INFO(dir_i);
	mutex_lock(&dir_f->sem);

	rd->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rd->nodetype = cpu_to_je16(JFFS2_NODETYPE_DIRENT);
	rd->totlen = cpu_to_je32(sizeof(*rd) + namelen);
	rd->hdr_crc = cpu_to_je32(crc32(0, rd, sizeof(struct jffs2_unknown_node)-4));

	rd->pino = cpu_to_je32(dir_i->i_ino);
	rd->version = cpu_to_je32(++dir_f->highest_version);
	rd->ino = cpu_to_je32(inode->i_ino);
	rd->mctime = cpu_to_je32(JFFS2_NOW());
	rd->nsize = namelen;
	rd->type = DT_DIR;
	rd->node_crc = cpu_to_je32(crc32(0, rd, sizeof(*rd)-8));
	rd->name_crc = cpu_to_je32(crc32(0, dentry->d_name.name, namelen));

	fd = jffs2_write_dirent(c, dir_f, rd, dentry->d_name.name, namelen, ALLOC_NORMAL);

	if (IS_ERR(fd)) {
		/* dirent failed to write. Delete the inode normally
		   as if it were the final unlink() */
		jffs2_complete_reservation(c);
		jffs2_free_raw_dirent(rd);
		mutex_unlock(&dir_f->sem);
		ret = PTR_ERR(fd);
		goto fail;
	}

	dir_i->i_mtime = dir_i->i_ctime = ITIME(je32_to_cpu(rd->mctime));
	inc_nlink(dir_i);

	jffs2_free_raw_dirent(rd);

	/* Link the fd into the inode's list, obsoleting an old
	   one if necessary. */
	jffs2_add_fd_to_list(c, fd, &dir_f->dents);

	mutex_unlock(&dir_f->sem);
	jffs2_complete_reservation(c);

	d_instantiate_new(dentry, inode);
	return 0;

 fail:
	iget_failed(inode);
	return ret;
}