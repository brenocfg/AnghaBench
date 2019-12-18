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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int zend_bool ;

/* Variables and functions */
 scalar_t__ zend_string_equals_literal_ci (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static zend_bool is_generator_compatible_class_type(zend_string *name) {
	return zend_string_equals_literal_ci(name, "Traversable")
		|| zend_string_equals_literal_ci(name, "Iterator")
		|| zend_string_equals_literal_ci(name, "Generator");
}