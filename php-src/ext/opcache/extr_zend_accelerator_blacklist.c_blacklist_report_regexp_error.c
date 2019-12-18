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
 int /*<<< orphan*/  ACCEL_LOG_ERROR ; 
 int /*<<< orphan*/  zend_accel_error (int /*<<< orphan*/ ,char*,int,char const*) ; 

__attribute__((used)) static void blacklist_report_regexp_error(const char *pcre_error, int pcre_error_offset)
{
	zend_accel_error(ACCEL_LOG_ERROR, "Blacklist compilation failed (offset: %d), %s\n", pcre_error_offset, pcre_error);
}