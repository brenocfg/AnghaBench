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
struct seq_file {int dummy; } ;
struct file {struct seq_file* private_data; } ;
struct afs_net {int dummy; } ;
struct afs_cell {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CELL_FL_NO_GC ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct afs_cell*) ; 
 int PTR_ERR (struct afs_cell*) ; 
 int /*<<< orphan*/  _debug (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 struct afs_cell* afs_lookup_cell (struct afs_net*,char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  afs_put_cell (struct afs_net*,struct afs_cell*) ; 
 struct afs_net* afs_seq2net (struct seq_file*) ; 
 char* memchr (char*,char,size_t) ; 
 int /*<<< orphan*/  printk (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_proc_cells_write(struct file *file, char *buf, size_t size)
{
	struct seq_file *m = file->private_data;
	struct afs_net *net = afs_seq2net(m);
	char *name, *args;
	int ret;

	/* trim to first NL */
	name = memchr(buf, '\n', size);
	if (name)
		*name = 0;

	/* split into command, name and argslist */
	name = strchr(buf, ' ');
	if (!name)
		goto inval;
	do {
		*name++ = 0;
	} while(*name == ' ');
	if (!*name)
		goto inval;

	args = strchr(name, ' ');
	if (args) {
		do {
			*args++ = 0;
		} while(*args == ' ');
		if (!*args)
			goto inval;
	}

	/* determine command to perform */
	_debug("cmd=%s name=%s args=%s", buf, name, args);

	if (strcmp(buf, "add") == 0) {
		struct afs_cell *cell;

		cell = afs_lookup_cell(net, name, strlen(name), args, true);
		if (IS_ERR(cell)) {
			ret = PTR_ERR(cell);
			goto done;
		}

		if (test_and_set_bit(AFS_CELL_FL_NO_GC, &cell->flags))
			afs_put_cell(net, cell);
	} else {
		goto inval;
	}

	ret = 0;

done:
	_leave(" = %d", ret);
	return ret;

inval:
	ret = -EINVAL;
	printk("kAFS: Invalid Command on /proc/fs/afs/cells file\n");
	goto done;
}