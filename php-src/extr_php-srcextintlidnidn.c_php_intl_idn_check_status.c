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
typedef  int /*<<< orphan*/  UErrorCode ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  get_active_function_name () ; 
 int /*<<< orphan*/  intl_error_set_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_set_custom_msg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int php_intl_idn_check_status(UErrorCode err, const char *msg)
{
	intl_error_set_code(NULL, err);
	if (U_FAILURE(err)) {
		char *buff;
		spprintf(&buff, 0, "%s: %s",
			get_active_function_name(),
			msg);
		intl_error_set_custom_msg(NULL, buff, 1);
		efree(buff);
		return FAILURE;
	}

	return SUCCESS;
}