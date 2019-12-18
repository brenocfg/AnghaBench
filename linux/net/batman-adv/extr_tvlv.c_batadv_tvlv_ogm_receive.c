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
typedef  int /*<<< orphan*/  u16 ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_ogm_packet {int /*<<< orphan*/  tvlv_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_tvlv_containers_process (struct batadv_priv*,int,struct batadv_orig_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

void batadv_tvlv_ogm_receive(struct batadv_priv *bat_priv,
			     struct batadv_ogm_packet *batadv_ogm_packet,
			     struct batadv_orig_node *orig_node)
{
	void *tvlv_value;
	u16 tvlv_value_len;

	if (!batadv_ogm_packet)
		return;

	tvlv_value_len = ntohs(batadv_ogm_packet->tvlv_len);
	if (!tvlv_value_len)
		return;

	tvlv_value = batadv_ogm_packet + 1;

	batadv_tvlv_containers_process(bat_priv, true, orig_node, NULL, NULL,
				       tvlv_value, tvlv_value_len);
}