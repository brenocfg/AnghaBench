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
struct sctp_tsnmap {scalar_t__ base_tsn; scalar_t__ len; int /*<<< orphan*/  tsn_map; int /*<<< orphan*/  cumulative_tsn_ack_point; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ SCTP_TSN_MAP_SIZE ; 
 int /*<<< orphan*/  TSN_lt (scalar_t__,scalar_t__) ; 
 scalar_t__ TSN_lte (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

int sctp_tsnmap_check(const struct sctp_tsnmap *map, __u32 tsn)
{
	u32 gap;

	/* Check to see if this is an old TSN */
	if (TSN_lte(tsn, map->cumulative_tsn_ack_point))
		return 1;

	/* Verify that we can hold this TSN and that it will not
	 * overlfow our map
	 */
	if (!TSN_lt(tsn, map->base_tsn + SCTP_TSN_MAP_SIZE))
		return -1;

	/* Calculate the index into the mapping arrays.  */
	gap = tsn - map->base_tsn;

	/* Check to see if TSN has already been recorded.  */
	if (gap < map->len && test_bit(gap, map->tsn_map))
		return 1;
	else
		return 0;
}