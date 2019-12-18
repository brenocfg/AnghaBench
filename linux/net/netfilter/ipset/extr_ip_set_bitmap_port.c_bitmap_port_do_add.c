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
typedef  int /*<<< orphan*/  u32 ;
struct bitmap_port_adt_elem {int /*<<< orphan*/  id; } ;
struct bitmap_port {int /*<<< orphan*/  members; } ;

/* Variables and functions */
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bitmap_port_do_add(const struct bitmap_port_adt_elem *e,
		   struct bitmap_port *map, u32 flags, size_t dsize)
{
	return !!test_bit(e->id, map->members);
}