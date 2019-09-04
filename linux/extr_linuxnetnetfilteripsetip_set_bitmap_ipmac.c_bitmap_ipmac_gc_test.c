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
typedef  int /*<<< orphan*/  u16 ;
struct bitmap_ipmac_elem {scalar_t__ filled; } ;
struct bitmap_ipmac {int /*<<< orphan*/  extensions; int /*<<< orphan*/  members; } ;

/* Variables and functions */
 scalar_t__ MAC_FILLED ; 
 struct bitmap_ipmac_elem* get_const_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bitmap_ipmac_gc_test(u16 id, const struct bitmap_ipmac *map, size_t dsize)
{
	const struct bitmap_ipmac_elem *elem;

	if (!test_bit(id, map->members))
		return 0;
	elem = get_const_elem(map->extensions, id, dsize);
	/* Timer not started for the incomplete elements */
	return elem->filled == MAC_FILLED;
}