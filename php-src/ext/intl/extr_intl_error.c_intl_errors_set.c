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
typedef  int /*<<< orphan*/  UErrorCode ;

/* Variables and functions */
 int /*<<< orphan*/  intl_errors_set_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_errors_set_custom_msg (int /*<<< orphan*/ *,char const*,int) ; 

void intl_errors_set( intl_error* err, UErrorCode code, const char* msg, int copyMsg )
{
	intl_errors_set_code( err, code );
	intl_errors_set_custom_msg( err, msg, copyMsg );
}