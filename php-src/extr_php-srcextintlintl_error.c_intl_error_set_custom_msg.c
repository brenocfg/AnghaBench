#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int free_custom_error_message; char* custom_error_message; } ;
typedef  TYPE_1__ intl_error ;

/* Variables and functions */
 scalar_t__ INTL_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntlException_ce_ptr ; 
 int /*<<< orphan*/  error_level ; 
 char* estrdup (char const*) ; 
 int /*<<< orphan*/  intl_free_custom_error_msg (TYPE_1__*) ; 
 TYPE_1__* intl_g_error_get () ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,scalar_t__,char*,char const*) ; 
 int /*<<< orphan*/  use_exceptions ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 

void intl_error_set_custom_msg( intl_error* err, const char* msg, int copyMsg )
{
	if( !msg )
		return;

	if( !err ) {
		if( INTL_G( error_level ) )
			php_error_docref( NULL, INTL_G( error_level ), "%s", msg );
		if( INTL_G( use_exceptions ) )
			zend_throw_exception_ex( IntlException_ce_ptr, 0, "%s", msg );
	}
	if( !err && !( err = intl_g_error_get(  ) ) )
		return;

	/* Free previous message if any */
	intl_free_custom_error_msg( err );

	/* Mark message copied if any */
	err->free_custom_error_message = copyMsg;

	/* Set user's error text message */
	err->custom_error_message = copyMsg ? estrdup( msg ) : (char *) msg;
}