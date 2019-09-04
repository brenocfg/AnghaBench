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
struct cw1200_debug_priv {int /*<<< orphan*/  debugfs_phy; } ;
struct cw1200_common {struct cw1200_debug_priv* debug; TYPE_2__* hw; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct TYPE_3__ {int /*<<< orphan*/  debugfsdir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct cw1200_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fops_counters ; 
 int /*<<< orphan*/  fops_status ; 
 int /*<<< orphan*/  fops_wsm_dumps ; 
 int /*<<< orphan*/  kfree (struct cw1200_debug_priv*) ; 
 struct cw1200_debug_priv* kzalloc (int,int /*<<< orphan*/ ) ; 

int cw1200_debug_init(struct cw1200_common *priv)
{
	int ret = -ENOMEM;
	struct cw1200_debug_priv *d = kzalloc(sizeof(struct cw1200_debug_priv),
			GFP_KERNEL);
	priv->debug = d;
	if (!d)
		return ret;

	d->debugfs_phy = debugfs_create_dir("cw1200",
					    priv->hw->wiphy->debugfsdir);
	if (!d->debugfs_phy)
		goto err;

	if (!debugfs_create_file("status", 0400, d->debugfs_phy,
				 priv, &fops_status))
		goto err;

	if (!debugfs_create_file("counters", 0400, d->debugfs_phy,
				 priv, &fops_counters))
		goto err;

	if (!debugfs_create_file("wsm_dumps", 0200, d->debugfs_phy,
				 priv, &fops_wsm_dumps))
		goto err;

	return 0;

err:
	priv->debug = NULL;
	debugfs_remove_recursive(d->debugfs_phy);
	kfree(d);
	return ret;
}