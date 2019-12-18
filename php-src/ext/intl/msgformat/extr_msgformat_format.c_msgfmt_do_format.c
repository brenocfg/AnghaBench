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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int /*<<< orphan*/  MessageFormatter_object ;

/* Variables and functions */
 int /*<<< orphan*/  INTL_DATA_ERROR_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTL_METHOD_RETVAL_UTF8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RETURN_FALSE ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umsg_format_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msgfmt_do_format(MessageFormatter_object *mfo, zval *args, zval *return_value)
{
	UChar* formatted = NULL;
	int32_t formatted_len = 0;

	umsg_format_helper(mfo, Z_ARRVAL_P(args), &formatted, &formatted_len);

	if (U_FAILURE(INTL_DATA_ERROR_CODE(mfo))) {
		if (formatted) {
			efree(formatted);
		}
		RETURN_FALSE;
	} else {
		INTL_METHOD_RETVAL_UTF8(mfo, formatted, formatted_len, 1);
	}
}