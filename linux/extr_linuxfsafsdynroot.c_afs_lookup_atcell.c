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
struct dentry {int /*<<< orphan*/  d_parent; } ;
struct afs_net {int /*<<< orphan*/  cells_lock; int /*<<< orphan*/  ws_cell; } ;
struct afs_cell {int name_len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AFS_MAXCELLNAME ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct afs_net* afs_d2net (struct dentry*) ; 
 int /*<<< orphan*/  done_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ need_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 struct afs_cell* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_seqbegin_or_lock (int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static struct dentry *afs_lookup_atcell(struct dentry *dentry)
{
	struct afs_cell *cell;
	struct afs_net *net = afs_d2net(dentry);
	struct dentry *ret;
	unsigned int seq = 0;
	char *name;
	int len;

	if (!net->ws_cell)
		return ERR_PTR(-ENOENT);

	ret = ERR_PTR(-ENOMEM);
	name = kmalloc(AFS_MAXCELLNAME + 1, GFP_KERNEL);
	if (!name)
		goto out_p;

	rcu_read_lock();
	do {
		read_seqbegin_or_lock(&net->cells_lock, &seq);
		cell = rcu_dereference_raw(net->ws_cell);
		if (cell) {
			len = cell->name_len;
			memcpy(name, cell->name, len + 1);
		}
	} while (need_seqretry(&net->cells_lock, seq));
	done_seqretry(&net->cells_lock, seq);
	rcu_read_unlock();

	ret = ERR_PTR(-ENOENT);
	if (!cell)
		goto out_n;

	ret = lookup_one_len(name, dentry->d_parent, len);

	/* We don't want to d_add() the @cell dentry here as we don't want to
	 * the cached dentry to hide changes to the local cell name.
	 */

out_n:
	kfree(name);
out_p:
	return ret;
}