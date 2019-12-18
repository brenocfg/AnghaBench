#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_9__ {TYPE_2__ array; } ;
typedef  TYPE_3__ zend_ffi_type ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {scalar_t__ key; TYPE_1__ it; } ;
typedef  TYPE_4__ zend_ffi_cdata_iterator ;
struct TYPE_11__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ zend_ffi_cdata ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 TYPE_3__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_OBJ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zend_ffi_cdata_it_valid(zend_object_iterator *it) /* {{{ */
{
	zend_ffi_cdata_iterator *iter = (zend_ffi_cdata_iterator*)it;
	zend_ffi_cdata *cdata = (zend_ffi_cdata*)Z_OBJ(iter->it.data);
	zend_ffi_type  *type = ZEND_FFI_TYPE(cdata->type);

	return (iter->key >= 0 && iter->key < type->array.length) ? SUCCESS : FAILURE;
}