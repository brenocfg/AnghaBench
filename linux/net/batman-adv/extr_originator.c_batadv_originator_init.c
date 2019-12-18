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
struct batadv_priv {int /*<<< orphan*/  orig_work; scalar_t__ orig_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ORIG_WORK_PERIOD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_event_workqueue ; 
 scalar_t__ batadv_hash_new (int) ; 
 int /*<<< orphan*/  batadv_hash_set_lock_class (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_orig_hash_lock_class_key ; 
 int /*<<< orphan*/  batadv_purge_orig ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int batadv_originator_init(struct batadv_priv *bat_priv)
{
	if (bat_priv->orig_hash)
		return 0;

	bat_priv->orig_hash = batadv_hash_new(1024);

	if (!bat_priv->orig_hash)
		goto err;

	batadv_hash_set_lock_class(bat_priv->orig_hash,
				   &batadv_orig_hash_lock_class_key);

	INIT_DELAYED_WORK(&bat_priv->orig_work, batadv_purge_orig);
	queue_delayed_work(batadv_event_workqueue,
			   &bat_priv->orig_work,
			   msecs_to_jiffies(BATADV_ORIG_WORK_PERIOD));

	return 0;

err:
	return -ENOMEM;
}