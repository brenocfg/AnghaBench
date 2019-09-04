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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int BATADV_MAX_AGGREGATION_BYTES ; 
 scalar_t__ BATADV_OGM2_HLEN ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool batadv_v_ogm_aggr_packet(int buff_pos, int packet_len,
				     __be16 tvlv_len)
{
	int next_buff_pos = 0;

	next_buff_pos += buff_pos + BATADV_OGM2_HLEN;
	next_buff_pos += ntohs(tvlv_len);

	return (next_buff_pos <= packet_len) &&
	       (next_buff_pos <= BATADV_MAX_AGGREGATION_BYTES);
}