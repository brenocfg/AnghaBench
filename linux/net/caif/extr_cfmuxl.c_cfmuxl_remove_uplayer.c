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
typedef  int u8 ;
struct cfmuxl {int /*<<< orphan*/  receive_lock; int /*<<< orphan*/ * up_cache; int /*<<< orphan*/  srvl_list; } ;
struct cflayer {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int UP_CACHE_SIZE ; 
 struct cfmuxl* container_obj (struct cflayer*) ; 
 struct cflayer* get_from_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct cflayer *cfmuxl_remove_uplayer(struct cflayer *layr, u8 id)
{
	struct cflayer *up;
	struct cfmuxl *muxl = container_obj(layr);
	int idx = id % UP_CACHE_SIZE;

	if (id == 0) {
		pr_warn("Trying to remove control layer\n");
		return NULL;
	}

	spin_lock_bh(&muxl->receive_lock);
	up = get_from_id(&muxl->srvl_list, id);
	if (up == NULL)
		goto out;

	RCU_INIT_POINTER(muxl->up_cache[idx], NULL);
	list_del_rcu(&up->node);
out:
	spin_unlock_bh(&muxl->receive_lock);
	return up;
}