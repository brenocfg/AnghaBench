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
typedef  int /*<<< orphan*/  zend_bitset ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  zend_bitset_excl (int /*<<< orphan*/ ,int) ; 
 int zend_bitset_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int zend_bitset_pop_first(zend_bitset set, uint32_t len) {
	int i = zend_bitset_first(set, len);
	if (i >= 0) {
		zend_bitset_excl(set, i);
	}
	return i;
}