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
struct TYPE_2__ {int imgfmt; int fourcc; } ;

/* Variables and functions */
 TYPE_1__* fmt_table ; 

__attribute__((used)) static int find_xv_format(int imgfmt)
{
    for (int n = 0; fmt_table[n].imgfmt; n++) {
        if (fmt_table[n].imgfmt == imgfmt)
            return fmt_table[n].fourcc;
    }
    return 0;
}