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

/* Variables and functions */
 int /*<<< orphan*/  zend_isinf (double) ; 
 int /*<<< orphan*/  zend_isnan (double) ; 

__attribute__((used)) static inline int php_json_is_valid_double(double d) /* {{{ */
{
	return !zend_isinf(d) && !zend_isnan(d);
}