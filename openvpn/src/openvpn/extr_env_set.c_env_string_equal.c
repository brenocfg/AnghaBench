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
 int /*<<< orphan*/  ASSERT (char const*) ; 

__attribute__((used)) static bool
env_string_equal(const char *s1, const char *s2)
{
    int c1, c2;
    ASSERT(s1);
    ASSERT(s2);

    while (true)
    {
        c1 = *s1++;
        c2 = *s2++;
        if (c1 == '=')
        {
            c1 = 0;
        }
        if (c2 == '=')
        {
            c2 = 0;
        }
        if (!c1 && !c2)
        {
            return true;
        }
        if (c1 != c2)
        {
            break;
        }
    }
    return false;
}