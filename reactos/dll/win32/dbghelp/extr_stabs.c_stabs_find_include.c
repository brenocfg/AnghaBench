#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* include_defs ; 
 int num_include_def ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stabs_find_include(const char* file, unsigned long val)
{
    int		i;

    for (i = 0; i < num_include_def; i++)
    {
        if (val == include_defs[i].value &&
            strcmp(file, include_defs[i].name) == 0)
            return i;
    }
    return -1;
}