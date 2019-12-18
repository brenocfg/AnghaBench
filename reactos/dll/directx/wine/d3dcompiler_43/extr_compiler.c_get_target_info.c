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
struct target_info {int /*<<< orphan*/  name; } ;
typedef  int LONG ;

/* Variables and functions */
 int ARRAY_SIZE (struct target_info const*) ; 
 int strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct target_info const* targets_info ; 

__attribute__((used)) static const struct target_info * get_target_info(const char *target)
{
    LONG min = 0;
    LONG max = ARRAY_SIZE(targets_info) - 1;
    LONG cur;
    int res;

    while (min <= max)
    {
        cur = (min + max) / 2;
        res = strcmp(target, targets_info[cur].name);
        if (res < 0)
            max = cur - 1;
        else if (res > 0)
            min = cur + 1;
        else
            return &targets_info[cur];
    }

    return NULL;
}