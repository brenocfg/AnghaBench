#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct TYPE_4__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ pdo_firebird_stmt ;

/* Variables and functions */
#define  PDO_ATTR_CURSOR_NAME 128 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int firebird_stmt_get_attribute(pdo_stmt_t *stmt, zend_long attr, zval *val) /* {{{ */
{
	pdo_firebird_stmt *S = (pdo_firebird_stmt*)stmt->driver_data;

	switch (attr) {
		default:
			return 0;
		case PDO_ATTR_CURSOR_NAME:
			if (*S->name) {
				ZVAL_STRING(val, S->name);
			} else {
				ZVAL_NULL(val);
			}
			break;
	}
	return 1;
}