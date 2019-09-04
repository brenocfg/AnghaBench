#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct hfsplus_unistr {int dummy; } ;
struct hfsplus_attr_key {int /*<<< orphan*/  cnid; } ;
struct hfs_find_data {TYPE_3__* key; int /*<<< orphan*/  keyoffset; int /*<<< orphan*/  bnode; TYPE_1__* tree; } ;
struct dentry {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  key_len ;
struct TYPE_8__ {int /*<<< orphan*/  attr_tree; } ;
struct TYPE_6__ {int /*<<< orphan*/  key_name; } ;
struct TYPE_7__ {TYPE_2__ attr; } ;
struct TYPE_5__ {scalar_t__ max_key_len; } ;

/* Variables and functions */
 int EIO ; 
 int ENODATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HFSPLUS_ATTR_MAX_STRLEN ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 TYPE_4__* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int NLS_MAX_CHARSET_SIZE ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ XATTR_MAC_OSX_PREFIX_LEN ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ can_list (char*) ; 
 scalar_t__ copy_name (char*,char*,int) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,struct hfsplus_attr_key*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hfs_bnode_read_u16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hfs_brec_goto (struct hfs_find_data*,int) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int hfsplus_find_attr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct hfs_find_data*) ; 
 int hfsplus_listxattr_finder_info (struct dentry*,char*,size_t) ; 
 scalar_t__ hfsplus_uni2asc (int /*<<< orphan*/ ,struct hfsplus_unistr const*,char*,int*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int name_len (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

ssize_t hfsplus_listxattr(struct dentry *dentry, char *buffer, size_t size)
{
	ssize_t err;
	ssize_t res = 0;
	struct inode *inode = d_inode(dentry);
	struct hfs_find_data fd;
	u16 key_len = 0;
	struct hfsplus_attr_key attr_key;
	char *strbuf;
	int xattr_name_len;

	if ((!S_ISREG(inode->i_mode) &&
			!S_ISDIR(inode->i_mode)) ||
				HFSPLUS_IS_RSRC(inode))
		return -EOPNOTSUPP;

	res = hfsplus_listxattr_finder_info(dentry, buffer, size);
	if (res < 0)
		return res;
	else if (!HFSPLUS_SB(inode->i_sb)->attr_tree)
		return (res == 0) ? -EOPNOTSUPP : res;

	err = hfs_find_init(HFSPLUS_SB(inode->i_sb)->attr_tree, &fd);
	if (err) {
		pr_err("can't init xattr find struct\n");
		return err;
	}

	strbuf = kmalloc(NLS_MAX_CHARSET_SIZE * HFSPLUS_ATTR_MAX_STRLEN +
			XATTR_MAC_OSX_PREFIX_LEN + 1, GFP_KERNEL);
	if (!strbuf) {
		res = -ENOMEM;
		goto out;
	}

	err = hfsplus_find_attr(inode->i_sb, inode->i_ino, NULL, &fd);
	if (err) {
		if (err == -ENOENT) {
			if (res == 0)
				res = -ENODATA;
			goto end_listxattr;
		} else {
			res = err;
			goto end_listxattr;
		}
	}

	for (;;) {
		key_len = hfs_bnode_read_u16(fd.bnode, fd.keyoffset);
		if (key_len == 0 || key_len > fd.tree->max_key_len) {
			pr_err("invalid xattr key length: %d\n", key_len);
			res = -EIO;
			goto end_listxattr;
		}

		hfs_bnode_read(fd.bnode, &attr_key,
				fd.keyoffset, key_len + sizeof(key_len));

		if (be32_to_cpu(attr_key.cnid) != inode->i_ino)
			goto end_listxattr;

		xattr_name_len = NLS_MAX_CHARSET_SIZE * HFSPLUS_ATTR_MAX_STRLEN;
		if (hfsplus_uni2asc(inode->i_sb,
			(const struct hfsplus_unistr *)&fd.key->attr.key_name,
					strbuf, &xattr_name_len)) {
			pr_err("unicode conversion failed\n");
			res = -EIO;
			goto end_listxattr;
		}

		if (!buffer || !size) {
			if (can_list(strbuf))
				res += name_len(strbuf, xattr_name_len);
		} else if (can_list(strbuf)) {
			if (size < (res + name_len(strbuf, xattr_name_len))) {
				res = -ERANGE;
				goto end_listxattr;
			} else
				res += copy_name(buffer + res,
						strbuf, xattr_name_len);
		}

		if (hfs_brec_goto(&fd, 1))
			goto end_listxattr;
	}

end_listxattr:
	kfree(strbuf);
out:
	hfs_find_exit(&fd);
	return res;
}