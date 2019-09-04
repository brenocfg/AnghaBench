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
struct dentry {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/  debug_dir; TYPE_1__* debug_log; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_wait; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  batadv_log_fops ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct batadv_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int batadv_debug_log_setup(struct batadv_priv *bat_priv)
{
	struct dentry *d;

	if (!bat_priv->debug_dir)
		goto err;

	bat_priv->debug_log = kzalloc(sizeof(*bat_priv->debug_log), GFP_ATOMIC);
	if (!bat_priv->debug_log)
		goto err;

	spin_lock_init(&bat_priv->debug_log->lock);
	init_waitqueue_head(&bat_priv->debug_log->queue_wait);

	d = debugfs_create_file("log", 0400, bat_priv->debug_dir, bat_priv,
				&batadv_log_fops);
	if (!d)
		goto err;

	return 0;

err:
	return -ENOMEM;
}