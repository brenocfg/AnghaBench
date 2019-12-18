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
typedef  scalar_t__ zend_long ;

/* Variables and functions */

__attribute__((used)) static inline zend_long safe_shift_left(zend_long n, zend_long s) {
	return (zend_long) ((zend_ulong) n << (zend_ulong) s);
}