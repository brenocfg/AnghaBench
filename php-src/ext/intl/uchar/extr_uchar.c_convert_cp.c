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
typedef  scalar_t__ zend_long ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ UChar32 ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_STRING ; 
 int SUCCESS ; 
 int /*<<< orphan*/  U8_NEXT (int /*<<< orphan*/ ,scalar_t__,size_t,scalar_t__) ; 
 scalar_t__ UCHAR_MAX_VALUE ; 
 scalar_t__ UCHAR_MIN_VALUE ; 
 int /*<<< orphan*/  U_ILLEGAL_ARGUMENT_ERROR ; 
 scalar_t__ ZEND_SIZE_T_INT_OVFL (size_t) ; 
 scalar_t__ Z_LVAL_P (int /*<<< orphan*/ *) ; 
 size_t Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intl_error_set_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_set_custom_msg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int convert_cp(UChar32* pcp, zval *zcp) {
	zend_long cp = -1;

	if (Z_TYPE_P(zcp) == IS_LONG) {
		cp = Z_LVAL_P(zcp);
	} else if (Z_TYPE_P(zcp) == IS_STRING) {
		int32_t i = 0;
		size_t zcp_len = Z_STRLEN_P(zcp);

		if (ZEND_SIZE_T_INT_OVFL(zcp_len)) {
			intl_error_set_code(NULL, U_ILLEGAL_ARGUMENT_ERROR);
			intl_error_set_custom_msg(NULL, "Input string is too long.", 0);
			return FAILURE;
		}

		U8_NEXT(Z_STRVAL_P(zcp), i, zcp_len, cp);
		if ((size_t)i != zcp_len) {
			intl_error_set_code(NULL, U_ILLEGAL_ARGUMENT_ERROR);
			intl_error_set_custom_msg(NULL, "Passing a UTF-8 character for codepoint requires a string which is exactly one UTF-8 codepoint long.", 0);
			return FAILURE;
		}
	} else {
		intl_error_set_code(NULL, U_ILLEGAL_ARGUMENT_ERROR);
		intl_error_set_custom_msg(NULL, "Invalid parameter for unicode point.  Must be either integer or UTF-8 sequence.", 0);
		return FAILURE;
	}
	if ((cp < UCHAR_MIN_VALUE) || (cp > UCHAR_MAX_VALUE)) {
		intl_error_set_code(NULL, U_ILLEGAL_ARGUMENT_ERROR);
		intl_error_set_custom_msg(NULL, "Codepoint out of range", 0);
		return FAILURE;
	}
	*pcp = (UChar32)cp;
	return SUCCESS;
}