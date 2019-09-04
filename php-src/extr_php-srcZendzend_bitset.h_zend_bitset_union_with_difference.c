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
typedef  int* zend_bitset ;
typedef  size_t uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline void zend_bitset_union_with_difference(zend_bitset set1, zend_bitset set2, zend_bitset set3, zend_bitset set4, uint32_t len)
{
	uint32_t i;

	for (i = 0; i < len; i++) {
		set1[i] = set2[i] | (set3[i] & ~set4[i]);
	}
}