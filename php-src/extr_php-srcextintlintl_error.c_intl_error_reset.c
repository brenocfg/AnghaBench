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
struct TYPE_5__ {int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ intl_error ;

/* Variables and functions */
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  intl_free_custom_error_msg (TYPE_1__*) ; 
 TYPE_1__* intl_g_error_get () ; 

void intl_error_reset( intl_error* err )
{
	if( !err && !( err = intl_g_error_get(  ) ) )
		return;

	err->code = U_ZERO_ERROR;

	intl_free_custom_error_msg( err );
}