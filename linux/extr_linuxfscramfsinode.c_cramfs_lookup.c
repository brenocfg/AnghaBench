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
struct inode {unsigned int i_size; int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {char* name; int len; } ;
struct dentry {TYPE_1__ d_name; } ;
struct cramfs_inode {int namelen; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int CRAMFS_FLAG_SORTED_DIRS ; 
 scalar_t__ CRAMFS_MAXPATHLEN ; 
 TYPE_2__* CRAMFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int OFFSET (struct inode*) ; 
 struct cramfs_inode* cramfs_read (int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 struct inode* get_cramfs_inode (int /*<<< orphan*/ ,struct cramfs_inode*,int) ; 
 int memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_mutex ; 

__attribute__((used)) static struct dentry *cramfs_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
{
	unsigned int offset = 0;
	struct inode *inode = NULL;
	int sorted;

	mutex_lock(&read_mutex);
	sorted = CRAMFS_SB(dir->i_sb)->flags & CRAMFS_FLAG_SORTED_DIRS;
	while (offset < dir->i_size) {
		struct cramfs_inode *de;
		char *name;
		int namelen, retval;
		int dir_off = OFFSET(dir) + offset;

		de = cramfs_read(dir->i_sb, dir_off, sizeof(*de)+CRAMFS_MAXPATHLEN);
		name = (char *)(de+1);

		/* Try to take advantage of sorted directories */
		if (sorted && (dentry->d_name.name[0] < name[0]))
			break;

		namelen = de->namelen << 2;
		offset += sizeof(*de) + namelen;

		/* Quick check that the name is roughly the right length */
		if (((dentry->d_name.len + 3) & ~3) != namelen)
			continue;

		for (;;) {
			if (!namelen) {
				inode = ERR_PTR(-EIO);
				goto out;
			}
			if (name[namelen-1])
				break;
			namelen--;
		}
		if (namelen != dentry->d_name.len)
			continue;
		retval = memcmp(dentry->d_name.name, name, namelen);
		if (retval > 0)
			continue;
		if (!retval) {
			inode = get_cramfs_inode(dir->i_sb, de, dir_off);
			break;
		}
		/* else (retval < 0) */
		if (sorted)
			break;
	}
out:
	mutex_unlock(&read_mutex);
	return d_splice_alias(inode, dentry);
}