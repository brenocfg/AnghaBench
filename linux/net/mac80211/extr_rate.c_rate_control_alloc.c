#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_4__* ops; } ;
struct TYPE_7__ {TYPE_1__* wiphy; } ;
struct TYPE_6__ {struct dentry* rcdir; } ;
struct ieee80211_local {TYPE_3__ hw; TYPE_2__ debugfs; } ;
struct dentry {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* alloc ) (TYPE_3__*,struct dentry*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  debugfsdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct rate_control_ref*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ieee80211_rate_control_ops_get (char const*) ; 
 int /*<<< orphan*/  kfree (struct rate_control_ref*) ; 
 struct rate_control_ref* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcname_ops ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct dentry*) ; 

__attribute__((used)) static struct rate_control_ref *rate_control_alloc(const char *name,
					    struct ieee80211_local *local)
{
	struct dentry *debugfsdir = NULL;
	struct rate_control_ref *ref;

	ref = kmalloc(sizeof(struct rate_control_ref), GFP_KERNEL);
	if (!ref)
		return NULL;
	ref->ops = ieee80211_rate_control_ops_get(name);
	if (!ref->ops)
		goto free;

#ifdef CONFIG_MAC80211_DEBUGFS
	debugfsdir = debugfs_create_dir("rc", local->hw.wiphy->debugfsdir);
	local->debugfs.rcdir = debugfsdir;
	debugfs_create_file("name", 0400, debugfsdir, ref, &rcname_ops);
#endif

	ref->priv = ref->ops->alloc(&local->hw, debugfsdir);
	if (!ref->priv)
		goto free;
	return ref;

free:
	kfree(ref);
	return NULL;
}