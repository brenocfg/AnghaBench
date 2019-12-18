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
struct sctp_tsnmap {scalar_t__ base_tsn; scalar_t__ max_tsn_seen; scalar_t__ len; int /*<<< orphan*/  tsn_map; int /*<<< orphan*/  cumulative_tsn_ack_point; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ SCTP_TSN_MAP_SIZE ; 
 scalar_t__ TSN_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_shift_right (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sctp_tsnmap_update (struct sctp_tsnmap*) ; 

void sctp_tsnmap_skip(struct sctp_tsnmap *map, __u32 tsn)
{
	u32 gap;

	if (TSN_lt(tsn, map->base_tsn))
		return;
	if (!TSN_lt(tsn, map->base_tsn + SCTP_TSN_MAP_SIZE))
		return;

	/* Bump the max.  */
	if (TSN_lt(map->max_tsn_seen, tsn))
		map->max_tsn_seen = tsn;

	gap = tsn - map->base_tsn + 1;

	map->base_tsn += gap;
	map->cumulative_tsn_ack_point += gap;
	if (gap >= map->len) {
		/* If our gap is larger then the map size, just
		 * zero out the map.
		 */
		bitmap_zero(map->tsn_map, map->len);
	} else {
		/* If the gap is smaller than the map size,
		 * shift the map by 'gap' bits and update further.
		 */
		bitmap_shift_right(map->tsn_map, map->tsn_map, gap, map->len);
		sctp_tsnmap_update(map);
	}
}