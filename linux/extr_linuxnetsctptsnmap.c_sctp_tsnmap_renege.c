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
struct sctp_tsnmap {int /*<<< orphan*/  tsn_map; scalar_t__ base_tsn; scalar_t__ len; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ TSN_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 

void sctp_tsnmap_renege(struct sctp_tsnmap *map, __u32 tsn)
{
	u32 gap;

	if (TSN_lt(tsn, map->base_tsn))
		return;
	/* Assert: TSN is in range.  */
	if (!TSN_lt(tsn, map->base_tsn + map->len))
		return;

	gap = tsn - map->base_tsn;

	/* Pretend we never saw the TSN.  */
	clear_bit(gap, map->tsn_map);
}