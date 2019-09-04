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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_ffi_ctype ;

/* Variables and functions */
 int /*<<< orphan*/  zend_ffi_type_dtor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_ffi_ctype_free_obj(zend_object *object) /* {{{ */
{
	zend_ffi_ctype *ctype = (zend_ffi_ctype*)object;

	zend_ffi_type_dtor(ctype->type);
}