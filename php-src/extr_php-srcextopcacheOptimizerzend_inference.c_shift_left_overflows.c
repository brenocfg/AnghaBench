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
typedef  int zend_long ;
typedef  int zend_bool ;

/* Variables and functions */
 int SIZEOF_ZEND_LONG ; 

__attribute__((used)) static inline zend_bool shift_left_overflows(zend_long n, zend_long s) {
	/* This considers shifts that shift in the sign bit to be overflowing as well */
	if (n >= 0) {
		return s >= SIZEOF_ZEND_LONG * 8 - 1 || (n << s) < n;
	} else {
		return s >= SIZEOF_ZEND_LONG * 8 - 1 || (n << s) > n;
	}
}