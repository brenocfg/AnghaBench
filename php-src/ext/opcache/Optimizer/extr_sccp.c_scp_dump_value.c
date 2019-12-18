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
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_BOT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_TOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_const (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_dump_ht (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scp_dump_value(zval *zv) {
	if (IS_TOP(zv)) {
		fprintf(stderr, " top");
	} else if (IS_BOT(zv)) {
		fprintf(stderr, " bot");
	} else if (Z_TYPE_P(zv) == IS_ARRAY || IS_PARTIAL_ARRAY(zv)) {
		fprintf(stderr, " %s[", IS_PARTIAL_ARRAY(zv) ? "partial " : "");
		zend_dump_ht(Z_ARRVAL_P(zv));
		fprintf(stderr, "]");
	} else if (IS_PARTIAL_OBJECT(zv)) {
		fprintf(stderr, " {");
		zend_dump_ht(Z_ARRVAL_P(zv));
		fprintf(stderr, "}");
	} else {
		zend_dump_const(zv);
	}
}