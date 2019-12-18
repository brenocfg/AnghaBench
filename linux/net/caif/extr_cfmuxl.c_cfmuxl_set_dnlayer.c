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
struct cfmuxl {int /*<<< orphan*/  transmit_lock; int /*<<< orphan*/  frml_list; } ;
struct cflayer {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int cfmuxl_set_dnlayer(struct cflayer *layr, struct cflayer *dn, u8 phyid)
{
	struct cfmuxl *muxl = (struct cfmuxl *) layr;

	spin_lock_bh(&muxl->transmit_lock);
	list_add_rcu(&dn->node, &muxl->frml_list);
	spin_unlock_bh(&muxl->transmit_lock);
	return 0;
}