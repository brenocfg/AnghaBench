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
typedef  int u32 ;
struct bitmap_ipmac_elem {scalar_t__ filled; int /*<<< orphan*/  ether; } ;
struct bitmap_ipmac_adt_elem {int /*<<< orphan*/  ether; scalar_t__ add_mac; int /*<<< orphan*/  id; } ;
struct bitmap_ipmac {int /*<<< orphan*/  members; int /*<<< orphan*/  extensions; } ;

/* Variables and functions */
 int IPSET_ADD_FAILED ; 
 int IPSET_ADD_START_STORED_TIMEOUT ; 
 int IPSET_ADD_STORE_PLAIN_TIMEOUT ; 
 int IPSET_FLAG_EXIST ; 
 scalar_t__ MAC_FILLED ; 
 scalar_t__ MAC_UNSET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bitmap_ipmac_elem* get_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bitmap_ipmac_do_add(const struct bitmap_ipmac_adt_elem *e,
		    struct bitmap_ipmac *map, u32 flags, size_t dsize)
{
	struct bitmap_ipmac_elem *elem;

	elem = get_elem(map->extensions, e->id, dsize);
	if (test_bit(e->id, map->members)) {
		if (elem->filled == MAC_FILLED) {
			if (e->add_mac &&
			    (flags & IPSET_FLAG_EXIST) &&
			    !ether_addr_equal(e->ether, elem->ether)) {
				/* memcpy isn't atomic */
				clear_bit(e->id, map->members);
				smp_mb__after_atomic();
				ether_addr_copy(elem->ether, e->ether);
			}
			return IPSET_ADD_FAILED;
		} else if (!e->add_mac)
			/* Already added without ethernet address */
			return IPSET_ADD_FAILED;
		/* Fill the MAC address and trigger the timer activation */
		clear_bit(e->id, map->members);
		smp_mb__after_atomic();
		ether_addr_copy(elem->ether, e->ether);
		elem->filled = MAC_FILLED;
		return IPSET_ADD_START_STORED_TIMEOUT;
	} else if (e->add_mac) {
		/* We can store MAC too */
		ether_addr_copy(elem->ether, e->ether);
		elem->filled = MAC_FILLED;
		return 0;
	}
	elem->filled = MAC_UNSET;
	/* MAC is not stored yet, don't start timer */
	return IPSET_ADD_STORE_PLAIN_TIMEOUT;
}