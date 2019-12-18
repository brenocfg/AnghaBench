#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * dtor; } ;
typedef  TYPE_1__ zend_llist ;
typedef  int /*<<< orphan*/  llist_apply_with_arg_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  extension_name_cmp ; 
 scalar_t__ print_extension_info ; 
 int /*<<< orphan*/  zend_extensions ; 
 int /*<<< orphan*/  zend_llist_apply_with_argument (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_llist_copy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_llist_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_llist_sort (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_extensions(void) /* {{{ */
{
	zend_llist sorted_exts;

	zend_llist_copy(&sorted_exts, &zend_extensions);
	sorted_exts.dtor = NULL;
	zend_llist_sort(&sorted_exts, extension_name_cmp);
	zend_llist_apply_with_argument(&sorted_exts, (llist_apply_with_arg_func_t) print_extension_info, NULL);
	zend_llist_destroy(&sorted_exts);
}