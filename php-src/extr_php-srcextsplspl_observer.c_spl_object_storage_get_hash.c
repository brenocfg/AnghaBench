#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int /*<<< orphan*/  h; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ zend_hash_key ;
struct TYPE_8__ {int /*<<< orphan*/  ce; } ;
struct TYPE_7__ {scalar_t__ fptr_get_hash; TYPE_3__ std; } ;
typedef  TYPE_2__ spl_SplObjectStorage ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ IS_STRING ; 
 int SUCCESS ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJ_HANDLE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 int /*<<< orphan*/  zend_call_method_with_1_params (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_object_storage_get_hash(zend_hash_key *key, spl_SplObjectStorage *intern, zval *obj) {
	if (intern->fptr_get_hash) {
		zval rv;
		zend_call_method_with_1_params(
			&intern->std, intern->std.ce, &intern->fptr_get_hash, "getHash", &rv, obj);
		if (!Z_ISUNDEF(rv)) {
			if (Z_TYPE(rv) == IS_STRING) {
				key->key = Z_STR(rv);
				return SUCCESS;
			} else {
				zend_throw_exception(spl_ce_RuntimeException, "Hash needs to be a string", 0);

				zval_ptr_dtor(&rv);
				return FAILURE;
			}
		} else {
			return FAILURE;
		}
	} else {
		key->key = NULL;
		key->h = Z_OBJ_HANDLE_P(obj);
		return SUCCESS;
	}
}