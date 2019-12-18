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
 int** format_table ; 

__attribute__((used)) static int oss2format(int format)
{
    for (int n = 0; format_table[n][0] != -1; n++) {
        if (format_table[n][0] == format)
            return format_table[n][1];
    }
    return 0;
}