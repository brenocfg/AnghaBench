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
 int /*<<< orphan*/  isdigit (char const) ; 

__attribute__((used)) static int
isInteger(const char *value)
{
    size_t i;
    
    if (value == NULL)
        return 0;
    
    for (i=0; value[i]; i++)
        if (!isdigit(value[i]&0xFF))
            return 0;
    return 1;
}