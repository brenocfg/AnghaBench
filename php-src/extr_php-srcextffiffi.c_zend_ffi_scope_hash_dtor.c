#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {struct TYPE_5__* tags; struct TYPE_5__* symbols; } ;
typedef  TYPE_1__ zend_ffi_scope ;

/* Variables and functions */
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (TYPE_1__*) ; 

__attribute__((used)) static void zend_ffi_scope_hash_dtor(zval *zv) /* {{{ */
{
	zend_ffi_scope *scope = Z_PTR_P(zv);
	if (scope->symbols) {
		zend_hash_destroy(scope->symbols);
		free(scope->symbols);
	}
	if (scope->tags) {
		zend_hash_destroy(scope->tags);
		free(scope->tags);
	}
	free(scope);
}