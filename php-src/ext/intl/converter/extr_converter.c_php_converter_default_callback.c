#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct TYPE_4__ {int /*<<< orphan*/  src; } ;
typedef  TYPE_1__ php_converter_object ;
typedef  int int8_t ;
typedef  int /*<<< orphan*/  chars ;
typedef  int /*<<< orphan*/  UErrorCode ;

/* Variables and functions */
 scalar_t__ CONV_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RETVAL_STRINGL (char*,int) ; 
 int /*<<< orphan*/  THROW_UFAILURE (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
#define  UCNV_ILLEGAL 130 
#define  UCNV_IRREGULAR 129 
#define  UCNV_UNASSIGNED 128 
 int /*<<< orphan*/  U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_INVALID_STATE_ERROR ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_converter_throw_failure (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ucnv_getSubstChars (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_converter_default_callback(zval *return_value, zval *zobj, zend_long reason, zval *error) {
	ZVAL_DEREF(error);
	zval_ptr_dtor(error);
	ZVAL_LONG(error, U_ZERO_ERROR);
	/* Basic functionality so children can call parent::toUCallback() */
	switch (reason) {
		case UCNV_UNASSIGNED:
		case UCNV_ILLEGAL:
		case UCNV_IRREGULAR:
		{
			php_converter_object *objval = (php_converter_object*)CONV_GET(zobj);
			char chars[127];
			int8_t chars_len = sizeof(chars);
			UErrorCode uerror = U_ZERO_ERROR;
            if(!objval->src) {
                php_converter_throw_failure(objval, U_INVALID_STATE_ERROR, "Source Converter has not been initialized yet");
				chars[0] = 0x1A;
				chars[1] = 0;
				chars_len = 1;
                ZVAL_LONG(error, U_INVALID_STATE_ERROR);
                RETVAL_STRINGL(chars, chars_len);
                return;
            }

			/* Yes, this is fairly wasteful at first glance,
			 * but considering that the alternative is to store
			 * what's sent into setSubstChars() and the fact
			 * that this is an extremely unlikely codepath
			 * I'd rather take the CPU hit here, than waste time
			 * storing a value I'm unlikely to use.
			 */
			ucnv_getSubstChars(objval->src, chars, &chars_len, &uerror);
			if (U_FAILURE(uerror)) {
				THROW_UFAILURE(objval, "ucnv_getSubstChars", uerror);
				chars[0] = 0x1A;
				chars[1] = 0;
				chars_len = 1;
            	ZVAL_LONG(error, uerror);
			}
			RETVAL_STRINGL(chars, chars_len);
		}
	}
}