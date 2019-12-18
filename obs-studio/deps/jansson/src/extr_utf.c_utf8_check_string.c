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
 size_t utf8_check_first (char const) ; 
 int /*<<< orphan*/  utf8_check_full (char const*,size_t,int /*<<< orphan*/ *) ; 

int utf8_check_string(const char *string, size_t length)
{
    size_t i;

    for(i = 0; i < length; i++)
    {
        size_t count = utf8_check_first(string[i]);
        if(count == 0)
            return 0;
        else if(count > 1)
        {
            if(count > length - i)
                return 0;

            if(!utf8_check_full(&string[i], count, NULL))
                return 0;

            i += count - 1;
        }
    }

    return 1;
}