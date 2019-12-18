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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phpdbg_opline_class_breaks_dtor(zval *data) /* {{{ */
{
	zend_hash_destroy(Z_ARRVAL_P(data));
	efree(Z_ARRVAL_P(data));
}