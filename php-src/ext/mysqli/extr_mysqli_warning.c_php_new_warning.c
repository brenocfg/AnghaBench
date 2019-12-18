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
struct TYPE_3__ {int errorno; int /*<<< orphan*/  sqlstate; int /*<<< orphan*/  reason; } ;
typedef  TYPE_1__ MYSQLI_WARNING ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_DUPLICATE ; 
 int /*<<< orphan*/  ZVAL_UTF8_STRING (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UTF8_STRINGL (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ecalloc (int,int) ; 

__attribute__((used)) static
MYSQLI_WARNING *php_new_warning(const char *reason, int errorno)
{
	MYSQLI_WARNING *w;

	w = (MYSQLI_WARNING *)ecalloc(1, sizeof(MYSQLI_WARNING));

	ZVAL_UTF8_STRING(&(w->reason), reason, ZSTR_DUPLICATE);

	ZVAL_UTF8_STRINGL(&(w->sqlstate), "HY000", sizeof("HY000") - 1,  ZSTR_DUPLICATE);

	w->errorno = errorno;

	return w;
}