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
struct batadv_bla_claim {int /*<<< orphan*/  backbone_lock; struct batadv_bla_backbone_gw* backbone_gw; } ;
struct batadv_bla_backbone_gw {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct batadv_bla_backbone_gw *
batadv_bla_claim_get_backbone_gw(struct batadv_bla_claim *claim)
{
	struct batadv_bla_backbone_gw *backbone_gw;

	spin_lock_bh(&claim->backbone_lock);
	backbone_gw = claim->backbone_gw;
	kref_get(&backbone_gw->refcount);
	spin_unlock_bh(&claim->backbone_lock);

	return backbone_gw;
}