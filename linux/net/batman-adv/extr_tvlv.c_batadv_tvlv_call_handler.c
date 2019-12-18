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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct batadv_tvlv_handler {int (* unicast_handler ) (struct batadv_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  (* ogm_handler ) (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;} ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int /*<<< orphan*/  BATADV_TVLV_HANDLER_OGM_CALLED ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  stub1 (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int stub2 (struct batadv_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int batadv_tvlv_call_handler(struct batadv_priv *bat_priv,
				    struct batadv_tvlv_handler *tvlv_handler,
				    bool ogm_source,
				    struct batadv_orig_node *orig_node,
				    u8 *src, u8 *dst,
				    void *tvlv_value, u16 tvlv_value_len)
{
	if (!tvlv_handler)
		return NET_RX_SUCCESS;

	if (ogm_source) {
		if (!tvlv_handler->ogm_handler)
			return NET_RX_SUCCESS;

		if (!orig_node)
			return NET_RX_SUCCESS;

		tvlv_handler->ogm_handler(bat_priv, orig_node,
					  BATADV_NO_FLAGS,
					  tvlv_value, tvlv_value_len);
		tvlv_handler->flags |= BATADV_TVLV_HANDLER_OGM_CALLED;
	} else {
		if (!src)
			return NET_RX_SUCCESS;

		if (!dst)
			return NET_RX_SUCCESS;

		if (!tvlv_handler->unicast_handler)
			return NET_RX_SUCCESS;

		return tvlv_handler->unicast_handler(bat_priv, src,
						     dst, tvlv_value,
						     tvlv_value_len);
	}

	return NET_RX_SUCCESS;
}