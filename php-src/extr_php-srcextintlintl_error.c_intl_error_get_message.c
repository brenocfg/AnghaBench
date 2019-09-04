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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {scalar_t__ custom_error_message; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ intl_error ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTR_EMPTY_ALLOC () ; 
 TYPE_1__* intl_g_error_get () ; 
 int /*<<< orphan*/ * strpprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* u_errorName (int /*<<< orphan*/ ) ; 

zend_string * intl_error_get_message( intl_error* err )
{
	const char *uErrorName = NULL;
	zend_string *errMessage = 0;

	if( !err && !( err = intl_g_error_get(  ) ) )
		return ZSTR_EMPTY_ALLOC();

	uErrorName = u_errorName( err->code );

	/* Format output string */
	if( err->custom_error_message )
	{
		errMessage = strpprintf(0, "%s: %s", err->custom_error_message, uErrorName );
	}
	else
	{
		errMessage = strpprintf(0, "%s", uErrorName );
	}

	return errMessage;
}