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
struct super_block {scalar_t__ s_magic; TYPE_2__* s_type; int /*<<< orphan*/  const s_dev; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_fs_info; } ;
struct inode {TYPE_1__* i_op; } ;
struct dentry {struct super_block* d_sb; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  const dev_t ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {int /*<<< orphan*/  rename; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (char*) ; 
 int MAJOR (int /*<<< orphan*/  const) ; 
 int MINOR (int /*<<< orphan*/  const) ; 
 scalar_t__ PROC_SUPER_MAGIC ; 
 int /*<<< orphan*/  current ; 
 struct inode* d_backing_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char const*,int const) ; 
 int /*<<< orphan*/  simple_strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 void* strlen (char const*) ; 
 scalar_t__ const task_tgid_nr_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* tomoyo_get_dentry_path (struct dentry*,char* const,int const) ; 

__attribute__((used)) static char *tomoyo_get_local_path(struct dentry *dentry, char * const buffer,
				   const int buflen)
{
	struct super_block *sb = dentry->d_sb;
	char *pos = tomoyo_get_dentry_path(dentry, buffer, buflen);

	if (IS_ERR(pos))
		return pos;
	/* Convert from $PID to self if $PID is current thread. */
	if (sb->s_magic == PROC_SUPER_MAGIC && *pos == '/') {
		char *ep;
		const pid_t pid = (pid_t) simple_strtoul(pos + 1, &ep, 10);

		if (*ep == '/' && pid && pid ==
		    task_tgid_nr_ns(current, sb->s_fs_info)) {
			pos = ep - 5;
			if (pos < buffer)
				goto out;
			memmove(pos, "/self", 5);
		}
		goto prepend_filesystem_name;
	}
	/* Use filesystem name for unnamed devices. */
	if (!MAJOR(sb->s_dev))
		goto prepend_filesystem_name;
	{
		struct inode *inode = d_backing_inode(sb->s_root);

		/*
		 * Use filesystem name if filesystem does not support rename()
		 * operation.
		 */
		if (!inode->i_op->rename)
			goto prepend_filesystem_name;
	}
	/* Prepend device name. */
	{
		char name[64];
		int name_len;
		const dev_t dev = sb->s_dev;

		name[sizeof(name) - 1] = '\0';
		snprintf(name, sizeof(name) - 1, "dev(%u,%u):", MAJOR(dev),
			 MINOR(dev));
		name_len = strlen(name);
		pos -= name_len;
		if (pos < buffer)
			goto out;
		memmove(pos, name, name_len);
		return pos;
	}
	/* Prepend filesystem name. */
prepend_filesystem_name:
	{
		const char *name = sb->s_type->name;
		const int name_len = strlen(name);

		pos -= name_len + 1;
		if (pos < buffer)
			goto out;
		memmove(pos, name, name_len);
		pos[name_len] = ':';
	}
	return pos;
out:
	return ERR_PTR(-ENOMEM);
}