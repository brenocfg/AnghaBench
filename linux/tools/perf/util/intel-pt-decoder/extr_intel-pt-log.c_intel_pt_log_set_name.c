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
 scalar_t__ MAX_LOG_NAME ; 
 int /*<<< orphan*/  log_name ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

void intel_pt_log_set_name(const char *name)
{
	strncpy(log_name, name, MAX_LOG_NAME - 5);
	strcat(log_name, ".log");
}