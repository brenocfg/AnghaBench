#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int value; int /*<<< orphan*/  upper; } ;

/* Variables and functions */
 scalar_t__ SIZE (TYPE_1__*) ; 
 TYPE_1__* signames ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int
parse_signal(const char *signame)
{
    int i;
    for (i = 0; i < (int)SIZE(signames); ++i)
    {
        if (!strcmp(signame, signames[i].upper))
        {
            return signames[i].value;
        }
    }
    return -1;
}