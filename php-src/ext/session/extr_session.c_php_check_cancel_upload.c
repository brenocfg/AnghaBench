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
typedef  int zend_bool ;
struct TYPE_4__ {int /*<<< orphan*/  s; } ;
struct TYPE_5__ {TYPE_1__ key; } ;
typedef  TYPE_2__ php_session_rfc1867_progress ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_TRUE ; 
 int /*<<< orphan*/  PS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_REFVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_session_vars ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * zend_symtable_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_bool php_check_cancel_upload(php_session_rfc1867_progress *progress) /* {{{ */
{
	zval *progress_ary, *cancel_upload;

	if ((progress_ary = zend_symtable_find(Z_ARRVAL_P(Z_REFVAL(PS(http_session_vars))), progress->key.s)) == NULL) {
		return 0;
	}
	if (Z_TYPE_P(progress_ary) != IS_ARRAY) {
		return 0;
	}
	if ((cancel_upload = zend_hash_str_find(Z_ARRVAL_P(progress_ary), "cancel_upload", sizeof("cancel_upload") - 1)) == NULL) {
		return 0;
	}
	return Z_TYPE_P(cancel_upload) == IS_TRUE;
}