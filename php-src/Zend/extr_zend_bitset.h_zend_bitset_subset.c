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
typedef  int zend_bool ;
typedef  int* zend_bitset ;
typedef  size_t uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline zend_bool zend_bitset_subset(zend_bitset set1, zend_bitset set2, uint32_t len)
{
	uint32_t i;

	for (i = 0; i < len; i++) {
		if (set1[i] & ~set2[i]) {
			return 0;
		}
	}
	return 1;
}