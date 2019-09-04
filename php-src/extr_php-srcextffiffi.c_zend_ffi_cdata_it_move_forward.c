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
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ zend_ffi_cdata_iterator ;

/* Variables and functions */

__attribute__((used)) static void zend_ffi_cdata_it_move_forward(zend_object_iterator *it) /* {{{ */
{
	zend_ffi_cdata_iterator *iter = (zend_ffi_cdata_iterator*)it;
	iter->key++;
}