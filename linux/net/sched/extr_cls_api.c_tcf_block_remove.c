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
struct tcf_net {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  idr; } ;
struct tcf_block {int /*<<< orphan*/  index; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tcf_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_net_id ; 

__attribute__((used)) static void tcf_block_remove(struct tcf_block *block, struct net *net)
{
	struct tcf_net *tn = net_generic(net, tcf_net_id);

	spin_lock(&tn->idr_lock);
	idr_remove(&tn->idr, block->index);
	spin_unlock(&tn->idr_lock);
}