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
struct TYPE_2__ {scalar_t__ local_hash; } ;
struct batadv_priv {TYPE_1__ tt; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ batadv_hash_new (int) ; 
 int /*<<< orphan*/  batadv_hash_set_lock_class (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_tt_local_hash_lock_class_key ; 

__attribute__((used)) static int batadv_tt_local_init(struct batadv_priv *bat_priv)
{
	if (bat_priv->tt.local_hash)
		return 0;

	bat_priv->tt.local_hash = batadv_hash_new(1024);

	if (!bat_priv->tt.local_hash)
		return -ENOMEM;

	batadv_hash_set_lock_class(bat_priv->tt.local_hash,
				   &batadv_tt_local_hash_lock_class_key);

	return 0;
}