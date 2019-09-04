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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int ZEND_BITSET_BIT_NUM (int /*<<< orphan*/ ) ; 
 size_t ZEND_BITSET_ELM_NUM (int /*<<< orphan*/ ) ; 
 int Z_UL (int) ; 

__attribute__((used)) static inline void zend_bitset_incl(zend_bitset set, uint32_t n)
{
	set[ZEND_BITSET_ELM_NUM(n)] |= Z_UL(1) << ZEND_BITSET_BIT_NUM(n);
}