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
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ intl_error ;
typedef  int /*<<< orphan*/  UErrorCode ;

/* Variables and functions */
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 TYPE_1__* intl_g_error_get () ; 

UErrorCode intl_error_get_code( intl_error* err )
{
	if( !err && !( err = intl_g_error_get(  ) ) )
		return U_ZERO_ERROR;

	return err->code;
}