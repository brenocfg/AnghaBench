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
struct TYPE_2__ {char const* text; unsigned int num; } ;

/* Variables and functions */
 TYPE_1__* options ; 

__attribute__((used)) static const char *
option_name_lookup(unsigned optnum)
{
    size_t i;
    for (i=0; options[i].text; i++) {
        if (options[i].num == optnum)
            return options[i].text;
    }
    return 0;
}