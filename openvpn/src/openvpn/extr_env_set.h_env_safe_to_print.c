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
 scalar_t__ is_password_env_var (char const*) ; 

__attribute__((used)) static inline bool
env_safe_to_print(const char *str)
{
#ifndef UNSAFE_DEBUG
    if (is_password_env_var(str))
    {
        return false;
    }
#endif
    return true;
}