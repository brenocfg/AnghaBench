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

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  O2NM_MAX_NODES ; 
 int /*<<< orphan*/  memcpy (unsigned long*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  o2hb_live_node_bitmap ; 

__attribute__((used)) static void o2hb_fill_node_map_from_callback(unsigned long *map,
					     unsigned bytes)
{
	BUG_ON(bytes < (BITS_TO_LONGS(O2NM_MAX_NODES) * sizeof(unsigned long)));

	memcpy(map, &o2hb_live_node_bitmap, bytes);
}