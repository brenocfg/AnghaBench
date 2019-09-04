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
struct batadv_tvlv_container {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  container_list_lock; } ;
struct batadv_priv {TYPE_1__ tvlv; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_tvlv_container_put (struct batadv_tvlv_container*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_tvlv_container_remove(struct batadv_priv *bat_priv,
					 struct batadv_tvlv_container *tvlv)
{
	lockdep_assert_held(&bat_priv->tvlv.container_list_lock);

	if (!tvlv)
		return;

	hlist_del(&tvlv->list);

	/* first call to decrement the counter, second call to free */
	batadv_tvlv_container_put(tvlv);
	batadv_tvlv_container_put(tvlv);
}