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
typedef  void* zend_ulong ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
struct php_com_iterator {scalar_t__ key; int /*<<< orphan*/  zdata; int /*<<< orphan*/  code_page; int /*<<< orphan*/  v; int /*<<< orphan*/  safe_array; scalar_t__ sa_max; scalar_t__ ev; } ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  IEnumVARIANT_Next (scalar_t__,int,int /*<<< orphan*/ *,unsigned long*) ; 
 scalar_t__ IS_UNDEF ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ php_com_safearray_get_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_com_zval_from_variant (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void com_iter_move_forwards(zend_object_iterator *iter)
{
	struct php_com_iterator *I = (struct php_com_iterator*)Z_PTR(iter->data);
	unsigned long n_fetched;
	zval ptr;

	/* release current cached element */
	VariantClear(&I->v);

	if (Z_TYPE(I->zdata) != IS_UNDEF) {
		zval_ptr_dtor(&I->zdata);
		ZVAL_UNDEF(&I->zdata);
	}

	if (I->ev) {
		/* Get the next element */
		if (SUCCEEDED(IEnumVARIANT_Next(I->ev, 1, &I->v, &n_fetched)) && n_fetched > 0) {
			I->key++;
		} else {
			/* indicate that there are no more items */
			I->key = (zend_ulong)-1;
			return;
		}
	} else {
		/* safe array */
		if (I->key >= (ULONG) I->sa_max) {
			I->key = (zend_ulong)-1;
			return;
		}
		I->key++;
		if (php_com_safearray_get_elem(&I->safe_array, &I->v, (LONG)I->key) == 0) {
			I->key = (zend_ulong)-1;
			return;
		}
	}

	ZVAL_NULL(&ptr);
	php_com_zval_from_variant(&ptr, &I->v, I->code_page);
	/* php_com_wrap_variant(ptr, &I->v, I->code_page); */
	ZVAL_COPY_VALUE(&I->zdata, &ptr);
}