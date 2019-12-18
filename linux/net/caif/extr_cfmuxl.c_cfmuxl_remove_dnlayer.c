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
struct cfmuxl {int /*<<< orphan*/  transmit_lock; int /*<<< orphan*/  frml_list; int /*<<< orphan*/ * dn_cache; } ;
struct cflayer {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int DN_CACHE_SIZE ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 struct cfmuxl* container_obj (struct cflayer*) ; 
 struct cflayer* get_from_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct cflayer *cfmuxl_remove_dnlayer(struct cflayer *layr, u8 phyid)
{
	struct cfmuxl *muxl = container_obj(layr);
	struct cflayer *dn;
	int idx = phyid % DN_CACHE_SIZE;

	spin_lock_bh(&muxl->transmit_lock);
	RCU_INIT_POINTER(muxl->dn_cache[idx], NULL);
	dn = get_from_id(&muxl->frml_list, phyid);
	if (dn == NULL)
		goto out;

	list_del_rcu(&dn->node);
	caif_assert(dn != NULL);
out:
	spin_unlock_bh(&muxl->transmit_lock);
	return dn;
}