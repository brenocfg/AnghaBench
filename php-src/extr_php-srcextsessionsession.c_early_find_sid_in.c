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
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_bool ;
struct TYPE_3__ {int /*<<< orphan*/  sname_len; } ;
typedef  TYPE_1__ php_session_rfc1867_progress ;

/* Variables and functions */
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/ * PG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_COPY_DEREF (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_globals ; 
 int /*<<< orphan*/  session_name ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool early_find_sid_in(zval *dest, int where, php_session_rfc1867_progress *progress) /* {{{ */
{
	zval *ppid;

	if (Z_ISUNDEF(PG(http_globals)[where])) {
		return 0;
	}

	if ((ppid = zend_hash_str_find(Z_ARRVAL(PG(http_globals)[where]), PS(session_name), progress->sname_len))
			&& Z_TYPE_P(ppid) == IS_STRING) {
		zval_ptr_dtor(dest);
		ZVAL_COPY_DEREF(dest, ppid);
		return 1;
	}

	return 0;
}