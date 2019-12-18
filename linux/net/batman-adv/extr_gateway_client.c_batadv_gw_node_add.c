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
struct batadv_tvlv_gateway_data {scalar_t__ bandwidth_down; scalar_t__ bandwidth_up; } ;
struct TYPE_2__ {int /*<<< orphan*/  generation; int /*<<< orphan*/  gateway_list; int /*<<< orphan*/  list_lock; } ;
struct batadv_priv {TYPE_1__ gw; } ;
struct batadv_orig_node {int /*<<< orphan*/  orig; int /*<<< orphan*/  refcount; } ;
struct batadv_gw_node {int bandwidth_down; int bandwidth_up; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; struct batadv_orig_node* orig_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  batadv_gw_node_put (struct batadv_gw_node*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_gw_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int ntohl (scalar_t__) ; 

__attribute__((used)) static void batadv_gw_node_add(struct batadv_priv *bat_priv,
			       struct batadv_orig_node *orig_node,
			       struct batadv_tvlv_gateway_data *gateway)
{
	struct batadv_gw_node *gw_node;

	lockdep_assert_held(&bat_priv->gw.list_lock);

	if (gateway->bandwidth_down == 0)
		return;

	gw_node = kzalloc(sizeof(*gw_node), GFP_ATOMIC);
	if (!gw_node)
		return;

	kref_init(&gw_node->refcount);
	INIT_HLIST_NODE(&gw_node->list);
	kref_get(&orig_node->refcount);
	gw_node->orig_node = orig_node;
	gw_node->bandwidth_down = ntohl(gateway->bandwidth_down);
	gw_node->bandwidth_up = ntohl(gateway->bandwidth_up);

	kref_get(&gw_node->refcount);
	hlist_add_head_rcu(&gw_node->list, &bat_priv->gw.gateway_list);
	bat_priv->gw.generation++;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Found new gateway %pM -> gw bandwidth: %u.%u/%u.%u MBit\n",
		   orig_node->orig,
		   ntohl(gateway->bandwidth_down) / 10,
		   ntohl(gateway->bandwidth_down) % 10,
		   ntohl(gateway->bandwidth_up) / 10,
		   ntohl(gateway->bandwidth_up) % 10);

	/* don't return reference to new gw_node */
	batadv_gw_node_put(gw_node);
}