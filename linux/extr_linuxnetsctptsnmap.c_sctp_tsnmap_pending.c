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
typedef  scalar_t__ u32 ;
struct sctp_tsnmap {scalar_t__ cumulative_tsn_ack_point; scalar_t__ max_tsn_seen; scalar_t__ base_tsn; scalar_t__ len; int /*<<< orphan*/  tsn_map; } ;
typedef  scalar_t__ __u32 ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 scalar_t__ bitmap_weight (int /*<<< orphan*/ ,scalar_t__) ; 

__u16 sctp_tsnmap_pending(struct sctp_tsnmap *map)
{
	__u32 cum_tsn = map->cumulative_tsn_ack_point;
	__u32 max_tsn = map->max_tsn_seen;
	__u32 base_tsn = map->base_tsn;
	__u16 pending_data;
	u32 gap;

	pending_data = max_tsn - cum_tsn;
	gap = max_tsn - base_tsn;

	if (gap == 0 || gap >= map->len)
		goto out;

	pending_data -= bitmap_weight(map->tsn_map, gap + 1);
out:
	return pending_data;
}