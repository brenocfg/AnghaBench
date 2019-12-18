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
 char** exceptions ; 
 scalar_t__ strcmp (char const*,char const* const) ; 

__attribute__((used)) static int is_exception(const char *msg)
{
    const char *const *p;

    for (p = exceptions; *p; ++p)
        if (strcmp(msg, *p) == 0)
            return 1;
    return 0;
}