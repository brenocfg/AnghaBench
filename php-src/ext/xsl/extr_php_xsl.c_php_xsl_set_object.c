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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {void* ptr; } ;
typedef  TYPE_1__ xsl_object ;

/* Variables and functions */
 TYPE_1__* Z_XSL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsl_object_set_data (void*,int /*<<< orphan*/ *) ; 

void php_xsl_set_object(zval *wrapper, void *obj)
{
	xsl_object *object;

	object = Z_XSL_P(wrapper);
	object->ptr = obj;
	xsl_object_set_data(obj, wrapper);
}