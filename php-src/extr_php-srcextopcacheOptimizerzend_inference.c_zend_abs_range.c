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
typedef  int /*<<< orphan*/  zend_long ;
typedef  int zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_LONG_MIN ; 

__attribute__((used)) static inline zend_bool zend_abs_range(
		zend_long min, zend_long max, zend_long *abs_min, zend_long *abs_max) {
	if (min == ZEND_LONG_MIN) {
		/* Cannot take absolute value of LONG_MIN  */
		return 0;
	}

	if (min >= 0) {
		*abs_min = min;
		*abs_max = max;
	} else if (max <= 0) {
		*abs_min = -max;
		*abs_max = -min;
	} else {
		/* Range crossing zero */
		*abs_min = 0;
		*abs_max = MAX(max, -min);
	}

	return 1;
}