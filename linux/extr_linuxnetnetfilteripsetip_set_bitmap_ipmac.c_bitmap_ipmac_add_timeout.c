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
typedef  unsigned long u32 ;
struct ip_set_ext {unsigned long timeout; } ;
struct ip_set {unsigned long timeout; } ;
struct bitmap_ipmac_adt_elem {scalar_t__ add_mac; } ;
struct bitmap_ipmac {int dummy; } ;

/* Variables and functions */
 int IPSET_ADD_START_STORED_TIMEOUT ; 
 int /*<<< orphan*/  ip_set_timeout_set (unsigned long*,unsigned long) ; 

__attribute__((used)) static inline int
bitmap_ipmac_add_timeout(unsigned long *timeout,
			 const struct bitmap_ipmac_adt_elem *e,
			 const struct ip_set_ext *ext, struct ip_set *set,
			 struct bitmap_ipmac *map, int mode)
{
	u32 t = ext->timeout;

	if (mode == IPSET_ADD_START_STORED_TIMEOUT) {
		if (t == set->timeout)
			/* Timeout was not specified, get stored one */
			t = *timeout;
		ip_set_timeout_set(timeout, t);
	} else {
		/* If MAC is unset yet, we store plain timeout value
		 * because the timer is not activated yet
		 * and we can reuse it later when MAC is filled out,
		 * possibly by the kernel
		 */
		if (e->add_mac)
			ip_set_timeout_set(timeout, t);
		else
			*timeout = t;
	}
	return 0;
}