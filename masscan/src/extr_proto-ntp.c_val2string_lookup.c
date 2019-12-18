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
struct Val2String {char const* string; unsigned int value; } ;

/* Variables and functions */

__attribute__((used)) static const char *
val2string_lookup(const struct Val2String *list, unsigned val)
{
    unsigned i;
    for (i=0; list[i].string; i++) {
        if (list[i].value == val)
            return list[i].string;
    }
    return 0;
}