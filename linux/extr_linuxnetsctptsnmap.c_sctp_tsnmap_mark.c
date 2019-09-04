#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sctp_tsnmap {scalar_t__ base_tsn; scalar_t__ len; scalar_t__ max_tsn_seen; int /*<<< orphan*/  tsn_map; int /*<<< orphan*/  cumulative_tsn_ack_point; } ;
struct sctp_transport {TYPE_2__* asoc; int /*<<< orphan*/  sack_generation; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_3__ {int /*<<< orphan*/  sack_generation; } ;
struct TYPE_4__ {TYPE_1__ peer; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ TSN_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sctp_tsnmap_grow (struct sctp_tsnmap*,scalar_t__) ; 
 int /*<<< orphan*/  sctp_tsnmap_has_gap (struct sctp_tsnmap*) ; 
 int /*<<< orphan*/  sctp_tsnmap_update (struct sctp_tsnmap*) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

int sctp_tsnmap_mark(struct sctp_tsnmap *map, __u32 tsn,
		     struct sctp_transport *trans)
{
	u16 gap;

	if (TSN_lt(tsn, map->base_tsn))
		return 0;

	gap = tsn - map->base_tsn;

	if (gap >= map->len && !sctp_tsnmap_grow(map, gap + 1))
		return -ENOMEM;

	if (!sctp_tsnmap_has_gap(map) && gap == 0) {
		/* In this case the map has no gaps and the tsn we are
		 * recording is the next expected tsn.  We don't touch
		 * the map but simply bump the values.
		 */
		map->max_tsn_seen++;
		map->cumulative_tsn_ack_point++;
		if (trans)
			trans->sack_generation =
				trans->asoc->peer.sack_generation;
		map->base_tsn++;
	} else {
		/* Either we already have a gap, or about to record a gap, so
		 * have work to do.
		 *
		 * Bump the max.
		 */
		if (TSN_lt(map->max_tsn_seen, tsn))
			map->max_tsn_seen = tsn;

		/* Mark the TSN as received.  */
		set_bit(gap, map->tsn_map);

		/* Go fixup any internal TSN mapping variables including
		 * cumulative_tsn_ack_point.
		 */
		sctp_tsnmap_update(map);
	}

	return 0;
}