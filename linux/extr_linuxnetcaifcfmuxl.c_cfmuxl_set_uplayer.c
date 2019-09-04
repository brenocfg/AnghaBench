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
typedef  int /*<<< orphan*/  u8 ;
struct cfmuxl {int /*<<< orphan*/  receive_lock; int /*<<< orphan*/  srvl_list; } ;
struct cflayer {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 struct cfmuxl* container_obj (struct cflayer*) ; 
 struct cflayer* get_from_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int cfmuxl_set_uplayer(struct cflayer *layr, struct cflayer *up, u8 linkid)
{
	struct cfmuxl *muxl = container_obj(layr);
	struct cflayer *old;

	spin_lock_bh(&muxl->receive_lock);

	/* Two entries with same id is wrong, so remove old layer from mux */
	old = get_from_id(&muxl->srvl_list, linkid);
	if (old != NULL)
		list_del_rcu(&old->node);

	list_add_rcu(&up->node, &muxl->srvl_list);
	spin_unlock_bh(&muxl->receive_lock);

	return 0;
}