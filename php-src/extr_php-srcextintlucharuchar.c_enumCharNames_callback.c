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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int param_count; int /*<<< orphan*/ * params; int /*<<< orphan*/ * retval; } ;
struct TYPE_4__ {int /*<<< orphan*/  fci_cache; TYPE_2__ fci; } ;
typedef  TYPE_1__ enumCharNames_data ;
typedef  int /*<<< orphan*/  UCharNameChoice ;
typedef  int /*<<< orphan*/  UChar32 ;
typedef  int UBool ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  U_INTERNAL_PROGRAM_ERROR ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_set_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_set_custom_msg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_call_function (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UBool enumCharNames_callback(enumCharNames_data *context,
                                    UChar32 code, UCharNameChoice nameChoice,
                                    const char *name, int32_t length) {
	zval retval;
	zval args[3];

	ZVAL_NULL(&retval);
	ZVAL_LONG(&args[0], code);
	ZVAL_LONG(&args[1], nameChoice);
	ZVAL_STRINGL(&args[2], name, length);

	context->fci.retval = &retval;
	context->fci.param_count = 3;
	context->fci.params = args;

	if (zend_call_function(&context->fci, &context->fci_cache) == FAILURE) {
		intl_error_set_code(NULL, U_INTERNAL_PROGRAM_ERROR);
		intl_error_set_custom_msg(NULL, "enumCharNames callback failed", 0);
		zval_ptr_dtor(&retval);
		zval_ptr_dtor_str(&args[2]);
		return 0;
	}
	zval_ptr_dtor(&retval);
	zval_ptr_dtor_str(&args[2]);
	return 1;
}