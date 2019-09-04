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
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* alloc ) (int /*<<< orphan*/ *,struct dentry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* ieee80211_rate_control_ops_get (char const*) ; 
 int /*<<< orphan*/  kfree (struct rate_control_ref*) ; 
 struct rate_control_ref* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct dentry*) ; 

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