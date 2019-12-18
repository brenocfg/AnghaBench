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
struct inode {char* i_private; size_t i_size; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_sb; } ;
struct dentry {struct dentry* d_parent; } ;
struct autofs_sb_info {int flags; } ;
struct autofs_info {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int AUTOFS_SBI_CATATONIC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EACCES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int S_IFLNK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs_clean_ino (struct autofs_info*) ; 
 int /*<<< orphan*/  autofs_del_active (struct dentry*) ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 struct inode* autofs_get_inode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,struct dentry*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int autofs_dir_symlink(struct inode *dir,
			       struct dentry *dentry,
			       const char *symname)
{
	struct autofs_sb_info *sbi = autofs_sbi(dir->i_sb);
	struct autofs_info *ino = autofs_dentry_ino(dentry);
	struct autofs_info *p_ino;
	struct inode *inode;
	size_t size = strlen(symname);
	char *cp;

	pr_debug("%s <- %pd\n", symname, dentry);

	if (!autofs_oz_mode(sbi))
		return -EACCES;

	/* autofs_oz_mode() needs to allow path walks when the
	 * autofs mount is catatonic but the state of an autofs
	 * file system needs to be preserved over restarts.
	 */
	if (sbi->flags & AUTOFS_SBI_CATATONIC)
		return -EACCES;

	BUG_ON(!ino);

	autofs_clean_ino(ino);

	autofs_del_active(dentry);

	cp = kmalloc(size + 1, GFP_KERNEL);
	if (!cp)
		return -ENOMEM;

	strcpy(cp, symname);

	inode = autofs_get_inode(dir->i_sb, S_IFLNK | 0555);
	if (!inode) {
		kfree(cp);
		return -ENOMEM;
	}
	inode->i_private = cp;
	inode->i_size = size;
	d_add(dentry, inode);

	dget(dentry);
	atomic_inc(&ino->count);
	p_ino = autofs_dentry_ino(dentry->d_parent);
	if (p_ino && !IS_ROOT(dentry))
		atomic_inc(&p_ino->count);

	dir->i_mtime = current_time(dir);

	return 0;
}