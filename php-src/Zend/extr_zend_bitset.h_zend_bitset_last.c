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
typedef  int zend_ulong ;
typedef  int* zend_bitset ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int ZEND_BITSET_ELM_SIZE ; 
 int Z_UL (int) ; 

__attribute__((used)) static inline int zend_bitset_last(zend_bitset set, uint32_t len)
{
	uint32_t i = len;

	while (i > 0) {
		i--;
		if (set[i]) {
			int j = ZEND_BITSET_ELM_SIZE * 8 * i - 1;
			zend_ulong x = set[i];
			while (x != Z_UL(0)) {
				x = x >> Z_UL(1);
				j++;
			}
			return j;
		}
	}
	return -1; /* empty set */
}