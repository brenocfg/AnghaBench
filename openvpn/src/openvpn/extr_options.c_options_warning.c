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
 int /*<<< orphan*/  options_warning_safe (char*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

void
options_warning(char *actual, const char *expected)
{
    options_warning_safe(actual, expected, strlen(actual) + 1);
}