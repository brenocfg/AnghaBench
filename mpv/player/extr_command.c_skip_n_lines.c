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
 char* strchr (char*,char) ; 

__attribute__((used)) static char *skip_n_lines(char *text, int lines)
{
    while (text && lines > 0) {
        char *next = strchr(text, '\n');
        text = next ? next + 1 : NULL;
        lines--;
    }
    return text;
}