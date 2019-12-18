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
struct sctp_tsnmap_iter {scalar_t__ start; } ;
struct sctp_tsnmap {scalar_t__ cumulative_tsn_ack_point; } ;

/* Variables and functions */

__attribute__((used)) static void sctp_tsnmap_iter_init(const struct sctp_tsnmap *map,
				  struct sctp_tsnmap_iter *iter)
{
	/* Only start looking one past the Cumulative TSN Ack Point.  */
	iter->start = map->cumulative_tsn_ack_point + 1;
}