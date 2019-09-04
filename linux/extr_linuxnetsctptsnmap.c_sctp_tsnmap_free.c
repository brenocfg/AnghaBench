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
struct sctp_tsnmap {int /*<<< orphan*/  tsn_map; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void sctp_tsnmap_free(struct sctp_tsnmap *map)
{
	map->len = 0;
	kfree(map->tsn_map);
}