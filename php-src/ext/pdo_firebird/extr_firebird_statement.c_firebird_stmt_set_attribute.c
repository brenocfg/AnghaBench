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
typedef  int zend_long ;
struct TYPE_7__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  stmt; TYPE_1__* H; } ;
typedef  TYPE_3__ pdo_firebird_stmt ;
struct TYPE_6__ {int /*<<< orphan*/  isc_status; } ;

/* Variables and functions */
#define  PDO_ATTR_CURSOR_NAME 128 
 int /*<<< orphan*/  RECORD_ERROR (TYPE_2__*) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_dsql_set_cursor_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  try_convert_to_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int firebird_stmt_set_attribute(pdo_stmt_t *stmt, zend_long attr, zval *val) /* {{{ */
{
	pdo_firebird_stmt *S = (pdo_firebird_stmt*)stmt->driver_data;

	switch (attr) {
		default:
			return 0;
		case PDO_ATTR_CURSOR_NAME:
			if (!try_convert_to_string(val)) {
				return 0;
			}

			if (isc_dsql_set_cursor_name(S->H->isc_status, &S->stmt, Z_STRVAL_P(val),0)) {
				RECORD_ERROR(stmt);
				return 0;
			}
			strlcpy(S->name, Z_STRVAL_P(val), sizeof(S->name));
			break;
	}
	return 1;
}