#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  std; int /*<<< orphan*/ * output; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ ze_xmlwriter_object ;

/* Variables and functions */
 TYPE_1__* php_xmlwriter_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlBufferFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeTextWriter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xmlwriter_object_free_storage(zend_object *object)
{
	ze_xmlwriter_object *intern = php_xmlwriter_fetch_object(object);
	if (!intern) {
		return;
	}
	if (intern->ptr) {
		xmlFreeTextWriter(intern->ptr);
		intern->ptr = NULL;
	}
	if (intern->output) {
		xmlBufferFree(intern->output);
		intern->output = NULL;
	}
	zend_object_std_dtor(&intern->std);
}