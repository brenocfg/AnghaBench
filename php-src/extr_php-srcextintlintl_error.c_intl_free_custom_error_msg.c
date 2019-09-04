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
struct TYPE_4__ {scalar_t__ free_custom_error_message; int /*<<< orphan*/ * custom_error_message; } ;
typedef  TYPE_1__ intl_error ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 TYPE_1__* intl_g_error_get () ; 

__attribute__((used)) static void intl_free_custom_error_msg( intl_error* err )
{
	if( !err && !( err = intl_g_error_get(  ) ) )
		return;

	if(err->free_custom_error_message ) {
		efree( err->custom_error_message );
	}

	err->custom_error_message      = NULL;
	err->free_custom_error_message = 0;
}