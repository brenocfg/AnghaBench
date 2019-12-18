#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/ * rcdir; } ;
struct ieee80211_local {TYPE_2__ debugfs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rate_control_ref*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rate_control_free(struct ieee80211_local *local,
			      struct rate_control_ref *ctrl_ref)
{
	ctrl_ref->ops->free(ctrl_ref->priv);

#ifdef CONFIG_MAC80211_DEBUGFS
	debugfs_remove_recursive(local->debugfs.rcdir);
	local->debugfs.rcdir = NULL;
#endif

	kfree(ctrl_ref);
}