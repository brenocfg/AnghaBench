#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_5__ {int /*<<< orphan*/ * dirp; } ;
struct TYPE_6__ {TYPE_1__ dir; } ;
struct TYPE_7__ {int /*<<< orphan*/ * orig_path; TYPE_2__ u; } ;
typedef  TYPE_3__ spl_filesystem_object ;

/* Variables and functions */
 TYPE_3__* spl_filesystem_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_method (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

zend_function *spl_filesystem_object_get_method_check(zend_object **object, zend_string *method, const zval *key) /* {{{ */
{
	spl_filesystem_object *fsobj = spl_filesystem_from_obj(*object);

	if (fsobj->u.dir.dirp == NULL && fsobj->orig_path == NULL) {
		zend_function *func;
		zend_string *tmp = zend_string_init("_bad_state_ex", sizeof("_bad_state_ex") - 1, 0);
		func = zend_std_get_method(object, tmp, NULL);
		zend_string_release_ex(tmp, 0);
		return func;
	}

	return zend_std_get_method(object, method, key);
}