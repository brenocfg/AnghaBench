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
typedef  scalar_t__ zend_long ;
typedef  int zend_bool ;

/* Variables and functions */
 scalar_t__ ZEND_LONG_MAX ; 
 scalar_t__ ZEND_LONG_MIN ; 

__attribute__((used)) static inline zend_bool add_will_overflow(zend_long a, zend_long b) {
	return (b > 0 && a > ZEND_LONG_MAX - b)
		|| (b < 0 && a < ZEND_LONG_MIN - b);
}