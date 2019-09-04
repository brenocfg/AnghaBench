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
struct bitmap_ipmac_elem {scalar_t__ filled; int /*<<< orphan*/  ether; } ;
struct bitmap_ipmac_adt_elem {int /*<<< orphan*/  ether; scalar_t__ add_mac; int /*<<< orphan*/  id; } ;
struct bitmap_ipmac {int /*<<< orphan*/  extensions; int /*<<< orphan*/  members; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ MAC_FILLED ; 
 int ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bitmap_ipmac_elem* get_const_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bitmap_ipmac_do_test(const struct bitmap_ipmac_adt_elem *e,
		     const struct bitmap_ipmac *map, size_t dsize)
{
	const struct bitmap_ipmac_elem *elem;

	if (!test_bit(e->id, map->members))
		return 0;
	elem = get_const_elem(map->extensions, e->id, dsize);
	if (e->add_mac && elem->filled == MAC_FILLED)
		return ether_addr_equal(e->ether, elem->ether);
	/* Trigger kernel to fill out the ethernet address */
	return -EAGAIN;
}