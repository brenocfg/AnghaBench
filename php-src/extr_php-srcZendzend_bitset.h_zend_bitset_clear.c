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
typedef  int uint32_t ;

/* Variables and functions */
 int ZEND_BITSET_ELM_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void zend_bitset_clear(zend_bitset set, uint32_t len)
{
	memset(set, 0, len * ZEND_BITSET_ELM_SIZE);
}