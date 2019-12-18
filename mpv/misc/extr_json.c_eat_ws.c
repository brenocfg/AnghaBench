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

__attribute__((used)) static void eat_ws(char **src)
{
    while (1) {
        char c = **src;
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
            return;
        *src += 1;
    }
}