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
struct batadv_tvlv_tt_data {int dummy; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ batadv_is_my_mac (struct batadv_priv*,int /*<<< orphan*/ *) ; 
 int batadv_send_my_tt_response (struct batadv_priv*,struct batadv_tvlv_tt_data*,int /*<<< orphan*/ *) ; 
 int batadv_send_other_tt_response (struct batadv_priv*,struct batadv_tvlv_tt_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool batadv_send_tt_response(struct batadv_priv *bat_priv,
				    struct batadv_tvlv_tt_data *tt_data,
				    u8 *req_src, u8 *req_dst)
{
	if (batadv_is_my_mac(bat_priv, req_dst))
		return batadv_send_my_tt_response(bat_priv, tt_data, req_src);
	return batadv_send_other_tt_response(bat_priv, tt_data, req_src,
					     req_dst);
}