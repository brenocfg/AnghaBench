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
struct TYPE_5__ {int param_count; int /*<<< orphan*/ * params; int /*<<< orphan*/ * retval; } ;
struct TYPE_4__ {int /*<<< orphan*/  fci_cache; TYPE_2__ fci; } ;
typedef  TYPE_1__ enumCharType_data ;
typedef  int /*<<< orphan*/  UCharCategory ;
typedef  int /*<<< orphan*/  UChar32 ;
typedef  int UBool ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  U_INTERNAL_PROGRAM_ERROR ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intl_error_set_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_errors_set_custom_msg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_call_function (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UBool enumCharType_callback(enumCharType_data *context,
                                   UChar32 start, UChar32 limit,
                                   UCharCategory type) {
	zval retval;
	zval args[3];

	ZVAL_NULL(&retval);
	/* Note that $start is INclusive, while $limit is EXclusive
	 * Therefore (0, 32, 15) means CPs 0..31 are of type 15
	 */
	ZVAL_LONG(&args[0], start);
	ZVAL_LONG(&args[1], limit);
	ZVAL_LONG(&args[2], type);

	context->fci.retval = &retval;
	context->fci.param_count = 3;
	context->fci.params = args;

	if (zend_call_function(&context->fci, &context->fci_cache) == FAILURE) {
		intl_error_set_code(NULL, U_INTERNAL_PROGRAM_ERROR);
		intl_errors_set_custom_msg(NULL, "enumCharTypes callback failed", 0);
		zval_ptr_dtor(&retval);
		return 0;
	}
	zval_ptr_dtor(&retval);
	return 1;
}