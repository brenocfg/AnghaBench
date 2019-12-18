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
struct afs_net {int /*<<< orphan*/  cells_lock; int /*<<< orphan*/  ws_cell; } ;
struct afs_cell {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CELL_FL_NO_GC ; 
 scalar_t__ IS_ERR (struct afs_cell*) ; 
 int PTR_ERR (struct afs_cell*) ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  afs_get_cell (struct afs_cell*) ; 
 struct afs_cell* afs_lookup_cell (struct afs_net*,char const*,size_t,char const*,int) ; 
 int /*<<< orphan*/  afs_put_cell (struct afs_net*,struct afs_cell*) ; 
 struct afs_cell* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct afs_cell*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

int afs_cell_init(struct afs_net *net, const char *rootcell)
{
	struct afs_cell *old_root, *new_root;
	const char *cp, *vllist;
	size_t len;

	_enter("");

	if (!rootcell) {
		/* module is loaded with no parameters, or built statically.
		 * - in the future we might initialize cell DB here.
		 */
		_leave(" = 0 [no root]");
		return 0;
	}

	cp = strchr(rootcell, ':');
	if (!cp) {
		_debug("kAFS: no VL server IP addresses specified");
		vllist = NULL;
		len = strlen(rootcell);
	} else {
		vllist = cp + 1;
		len = cp - rootcell;
	}

	/* allocate a cell record for the root cell */
	new_root = afs_lookup_cell(net, rootcell, len, vllist, false);
	if (IS_ERR(new_root)) {
		_leave(" = %ld", PTR_ERR(new_root));
		return PTR_ERR(new_root);
	}

	if (!test_and_set_bit(AFS_CELL_FL_NO_GC, &new_root->flags))
		afs_get_cell(new_root);

	/* install the new cell */
	write_seqlock(&net->cells_lock);
	old_root = rcu_access_pointer(net->ws_cell);
	rcu_assign_pointer(net->ws_cell, new_root);
	write_sequnlock(&net->cells_lock);

	afs_put_cell(net, old_root);
	_leave(" = 0");
	return 0;
}