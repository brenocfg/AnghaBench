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
struct batadv_ogm2_packet {int /*<<< orphan*/  tvlv_len; } ;

/* Variables and functions */
 int BATADV_MAX_AGGREGATION_BYTES ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
batadv_v_ogm_aggr_packet(int buff_pos, int packet_len,
			 const struct batadv_ogm2_packet *ogm2_packet)
{
	int next_buff_pos = 0;

	/* check if there is enough space for the header */
	next_buff_pos += buff_pos + sizeof(*ogm2_packet);
	if (next_buff_pos > packet_len)
		return false;

	/* check if there is enough space for the optional TVLV */
	next_buff_pos += ntohs(ogm2_packet->tvlv_len);

	return (next_buff_pos <= packet_len) &&
	       (next_buff_pos <= BATADV_MAX_AGGREGATION_BYTES);
}