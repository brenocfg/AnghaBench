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
 int /*<<< orphan*/  pr_debug (char*,char const*,...) ; 
 int /*<<< orphan*/  setenv (char const*,char const*,int) ; 
 int /*<<< orphan*/  unsetenv (char const*) ; 

__attribute__((used)) static inline void
force_set_env(const char *var, const char *value)
{
	if (value) {
		setenv(var, value, 1);
		pr_debug("set env: %s=%s\n", var, value);
	} else {
		unsetenv(var);
		pr_debug("unset env: %s\n", var);
	}
}