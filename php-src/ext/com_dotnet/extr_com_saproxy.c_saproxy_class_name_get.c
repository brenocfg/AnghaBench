#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* php_com_saproxy_class_entry ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string* saproxy_class_name_get(const zend_object *object)
{
	return zend_string_copy(php_com_saproxy_class_entry->name);
}