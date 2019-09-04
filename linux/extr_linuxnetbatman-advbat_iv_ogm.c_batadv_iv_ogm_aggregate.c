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
struct batadv_forw_packet {int packet_len; unsigned long direct_link_flags; int /*<<< orphan*/  num_packets; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static void batadv_iv_ogm_aggregate(struct batadv_forw_packet *forw_packet_aggr,
				    const unsigned char *packet_buff,
				    int packet_len, bool direct_link)
{
	unsigned long new_direct_link_flag;

	skb_put_data(forw_packet_aggr->skb, packet_buff, packet_len);
	forw_packet_aggr->packet_len += packet_len;
	forw_packet_aggr->num_packets++;

	/* save packet direct link flag status */
	if (direct_link) {
		new_direct_link_flag = BIT(forw_packet_aggr->num_packets);
		forw_packet_aggr->direct_link_flags |= new_direct_link_flag;
	}
}