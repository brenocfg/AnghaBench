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
struct tcon_link {int /*<<< orphan*/  tl_flags; int /*<<< orphan*/  tl_time; struct cifs_tcon* tl_tcon; int /*<<< orphan*/  tl_uid; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_ses {int /*<<< orphan*/  linux_uid; } ;
struct cifs_sb_info {int /*<<< orphan*/  prune_tlinks; int /*<<< orphan*/  tlink_tree_lock; int /*<<< orphan*/  tlink_tree; struct tcon_link* master_tlink; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TCON_LINK_IN_TREE ; 
 int /*<<< orphan*/  TCON_LINK_MASTER ; 
 int /*<<< orphan*/  TLINK_IDLE_EXPIRE ; 
 int /*<<< orphan*/  cifsiod_wq ; 
 int /*<<< orphan*/  jiffies ; 
 struct tcon_link* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlink_rb_insert (int /*<<< orphan*/ *,struct tcon_link*) ; 

__attribute__((used)) static int mount_setup_tlink(struct cifs_sb_info *cifs_sb, struct cifs_ses *ses,
			     struct cifs_tcon *tcon)
{
	struct tcon_link *tlink;

	/* hang the tcon off of the superblock */
	tlink = kzalloc(sizeof(*tlink), GFP_KERNEL);
	if (tlink == NULL)
		return -ENOMEM;

	tlink->tl_uid = ses->linux_uid;
	tlink->tl_tcon = tcon;
	tlink->tl_time = jiffies;
	set_bit(TCON_LINK_MASTER, &tlink->tl_flags);
	set_bit(TCON_LINK_IN_TREE, &tlink->tl_flags);

	cifs_sb->master_tlink = tlink;
	spin_lock(&cifs_sb->tlink_tree_lock);
	tlink_rb_insert(&cifs_sb->tlink_tree, tlink);
	spin_unlock(&cifs_sb->tlink_tree_lock);

	queue_delayed_work(cifsiod_wq, &cifs_sb->prune_tlinks,
				TLINK_IDLE_EXPIRE);
	return 0;
}