#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct jffs2_sb_info {int dummy; } ;
struct jffs2_inode_info {int /*<<< orphan*/  sem; TYPE_1__* inocache; struct jffs2_full_dirent* dents; int /*<<< orphan*/  fragtree; TYPE_3__* metadata; } ;
struct jffs2_full_dirent {struct jffs2_full_dirent* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  raw; } ;
struct TYPE_5__ {scalar_t__ state; void* nodes; int /*<<< orphan*/  pino_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  INO_STATE_CHECKEDABSENT ; 
 scalar_t__ INO_STATE_CHECKING ; 
 int /*<<< orphan*/  INO_STATE_CLEARING ; 
 int /*<<< orphan*/  jffs2_del_ino_cache (struct jffs2_sb_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  jffs2_free_full_dirent (struct jffs2_full_dirent*) ; 
 int /*<<< orphan*/  jffs2_free_full_dnode (TYPE_3__*) ; 
 int /*<<< orphan*/  jffs2_kill_fragtree (int /*<<< orphan*/ *,struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_mark_node_obsolete (struct jffs2_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_set_inocache_state (struct jffs2_sb_info*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_xattr_delete_inode (struct jffs2_sb_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void jffs2_do_clear_inode(struct jffs2_sb_info *c, struct jffs2_inode_info *f)
{
	struct jffs2_full_dirent *fd, *fds;
	int deleted;

	jffs2_xattr_delete_inode(c, f->inocache);
	mutex_lock(&f->sem);
	deleted = f->inocache && !f->inocache->pino_nlink;

	if (f->inocache && f->inocache->state != INO_STATE_CHECKING)
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_CLEARING);

	if (f->metadata) {
		if (deleted)
			jffs2_mark_node_obsolete(c, f->metadata->raw);
		jffs2_free_full_dnode(f->metadata);
	}

	jffs2_kill_fragtree(&f->fragtree, deleted?c:NULL);

	fds = f->dents;
	while(fds) {
		fd = fds;
		fds = fd->next;
		jffs2_free_full_dirent(fd);
	}

	if (f->inocache && f->inocache->state != INO_STATE_CHECKING) {
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		if (f->inocache->nodes == (void *)f->inocache)
			jffs2_del_ino_cache(c, f->inocache);
	}

	mutex_unlock(&f->sem);
}