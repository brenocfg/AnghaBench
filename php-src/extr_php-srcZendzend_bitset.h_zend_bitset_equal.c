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
typedef  int /*<<< orphan*/  zend_bitset ;
typedef  int uint32_t ;

/* Variables and functions */
 int ZEND_BITSET_ELM_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline zend_bool zend_bitset_equal(zend_bitset set1, zend_bitset set2, uint32_t len)
{
    return memcmp(set1, set2, len * ZEND_BITSET_ELM_SIZE) == 0;
}