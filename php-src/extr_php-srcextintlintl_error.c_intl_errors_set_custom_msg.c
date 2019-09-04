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
typedef  int /*<<< orphan*/  intl_error ;

/* Variables and functions */
 int /*<<< orphan*/  intl_error_set_custom_msg (int /*<<< orphan*/ *,char const*,int) ; 

void intl_errors_set_custom_msg( intl_error* err, const char* msg, int copyMsg )
{
	if(err) {
		intl_error_set_custom_msg( err, msg, copyMsg );
	}
	intl_error_set_custom_msg( NULL, msg, copyMsg );
}