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
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  options_warning_safe_ml (int /*<<< orphan*/ ,char*,char const*,size_t) ; 

void
options_warning_safe(char *actual, const char *expected, size_t actual_n)
{
    options_warning_safe_ml(M_WARN, actual, expected, actual_n);
}