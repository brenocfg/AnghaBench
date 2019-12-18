#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_6__ {int /*<<< orphan*/  properties_info; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 scalar_t__ zend_hash_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_class_entry* find_first_definition(zend_class_entry *ce, zend_class_entry **traits, size_t current_trait, zend_string *prop_name, zend_class_entry *coliding_ce) /* {{{ */
{
	size_t i;

	if (coliding_ce == ce) {
		for (i = 0; i < current_trait; i++) {
			if (traits[i]
			 && zend_hash_exists(&traits[i]->properties_info, prop_name)) {
				return traits[i];
			}
		}
	}

	return coliding_ce;
}