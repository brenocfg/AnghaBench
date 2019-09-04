#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {int /*<<< orphan*/  std; } ;
typedef  TYPE_1__ xmlreader_object ;

/* Variables and functions */
 TYPE_1__* php_xmlreader_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlreader_free_resources (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

void xmlreader_objects_free_storage(zend_object *object)
{
	xmlreader_object *intern = php_xmlreader_fetch_object(object);

	zend_object_std_dtor(&intern->std);

	xmlreader_free_resources(intern);
}