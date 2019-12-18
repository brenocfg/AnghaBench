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
typedef  void* u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int /*<<< orphan*/  len; void* type; void* version; } ;
struct batadv_tvlv_container {int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; TYPE_1__ tvlv_hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  container_list_lock; int /*<<< orphan*/  container_list; } ;
struct batadv_priv {TYPE_2__ tvlv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 struct batadv_tvlv_container* batadv_tvlv_container_get (struct batadv_priv*,void*,void*) ; 
 int /*<<< orphan*/  batadv_tvlv_container_put (struct batadv_tvlv_container*) ; 
 int /*<<< orphan*/  batadv_tvlv_container_remove (struct batadv_priv*,struct batadv_tvlv_container*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_tvlv_container* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct batadv_tvlv_container*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void batadv_tvlv_container_register(struct batadv_priv *bat_priv,
				    u8 type, u8 version,
				    void *tvlv_value, u16 tvlv_value_len)
{
	struct batadv_tvlv_container *tvlv_old, *tvlv_new;

	if (!tvlv_value)
		tvlv_value_len = 0;

	tvlv_new = kzalloc(sizeof(*tvlv_new) + tvlv_value_len, GFP_ATOMIC);
	if (!tvlv_new)
		return;

	tvlv_new->tvlv_hdr.version = version;
	tvlv_new->tvlv_hdr.type = type;
	tvlv_new->tvlv_hdr.len = htons(tvlv_value_len);

	memcpy(tvlv_new + 1, tvlv_value, ntohs(tvlv_new->tvlv_hdr.len));
	INIT_HLIST_NODE(&tvlv_new->list);
	kref_init(&tvlv_new->refcount);

	spin_lock_bh(&bat_priv->tvlv.container_list_lock);
	tvlv_old = batadv_tvlv_container_get(bat_priv, type, version);
	batadv_tvlv_container_remove(bat_priv, tvlv_old);

	kref_get(&tvlv_new->refcount);
	hlist_add_head(&tvlv_new->list, &bat_priv->tvlv.container_list);
	spin_unlock_bh(&bat_priv->tvlv.container_list_lock);

	/* don't return reference to new tvlv_container */
	batadv_tvlv_container_put(tvlv_new);
}