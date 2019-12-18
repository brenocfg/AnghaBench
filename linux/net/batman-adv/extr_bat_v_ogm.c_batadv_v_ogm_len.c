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
struct sk_buff {scalar_t__ data; } ;
struct batadv_ogm2_packet {int /*<<< orphan*/  tvlv_len; } ;

/* Variables and functions */
 unsigned int BATADV_OGM2_HLEN ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int batadv_v_ogm_len(struct sk_buff *skb)
{
	struct batadv_ogm2_packet *ogm_packet;

	ogm_packet = (struct batadv_ogm2_packet *)skb->data;
	return BATADV_OGM2_HLEN + ntohs(ogm_packet->tvlv_len);
}