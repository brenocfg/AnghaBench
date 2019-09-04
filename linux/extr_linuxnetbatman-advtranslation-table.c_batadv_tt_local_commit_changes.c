#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  commit_lock; } ;
struct batadv_priv {TYPE_1__ tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_tt_local_commit_changes_nolock (struct batadv_priv*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void batadv_tt_local_commit_changes(struct batadv_priv *bat_priv)
{
	spin_lock_bh(&bat_priv->tt.commit_lock);
	batadv_tt_local_commit_changes_nolock(bat_priv);
	spin_unlock_bh(&bat_priv->tt.commit_lock);
}