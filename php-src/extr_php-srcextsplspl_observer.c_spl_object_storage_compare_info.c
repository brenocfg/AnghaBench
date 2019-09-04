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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_2__ {int /*<<< orphan*/  inf; } ;
typedef  TYPE_1__ spl_SplObjectStorageElement ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int ZEND_NORMALIZE_BOOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ compare_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_object_storage_compare_info(zval *e1, zval *e2) /* {{{ */
{
	spl_SplObjectStorageElement *s1 = (spl_SplObjectStorageElement*)Z_PTR_P(e1);
	spl_SplObjectStorageElement *s2 = (spl_SplObjectStorageElement*)Z_PTR_P(e2);
	zval result;

	if (compare_function(&result, &s1->inf, &s2->inf) == FAILURE) {
		return 1;
	}

	return ZEND_NORMALIZE_BOOL(Z_LVAL(result));
}