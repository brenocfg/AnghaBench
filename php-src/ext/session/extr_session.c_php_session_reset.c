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

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ PS (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ php_session_active ; 
 scalar_t__ php_session_initialize () ; 
 int /*<<< orphan*/  session_status ; 

__attribute__((used)) static int php_session_reset(void) /* {{{ */
{
	if (PS(session_status) == php_session_active
		&& php_session_initialize() == SUCCESS) {
		return SUCCESS;
	}
	return FAILURE;
}