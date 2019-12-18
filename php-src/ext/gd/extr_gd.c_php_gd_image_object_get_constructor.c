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
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_function ;

/* Variables and functions */
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static zend_function *php_gd_image_object_get_constructor(zend_object *object)
{
	zend_throw_error(NULL, "You cannot initialize a GdImage object except through helper functions");
	return NULL;
}