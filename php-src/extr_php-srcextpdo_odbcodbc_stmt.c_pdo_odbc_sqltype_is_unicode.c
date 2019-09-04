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
struct TYPE_3__ {int /*<<< orphan*/  assume_utf8; } ;
typedef  TYPE_1__ pdo_odbc_stmt ;
typedef  int SWORD ;

/* Variables and functions */

__attribute__((used)) static int pdo_odbc_sqltype_is_unicode(pdo_odbc_stmt *S, SWORD sqltype)
{
	if (!S->assume_utf8) return 0;
	switch (sqltype) {
#ifdef SQL_WCHAR
		case SQL_WCHAR:
			return 1;
#endif
#ifdef SQL_WLONGVARCHAR
		case SQL_WLONGVARCHAR:
			return 1;
#endif
#ifdef SQL_WVARCHAR
		case SQL_WVARCHAR:
			return 1;
#endif
		default:
			return 0;
	}
}