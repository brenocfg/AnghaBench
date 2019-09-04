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

__attribute__((used)) static int count_lines(char *text)
{
    int count = 0;
    while (text) {
        char *next = strchr(text, '\n');
        if (!next || (next[0] == '\n' && !next[1]))
            break;
        text = next + 1;
        count++;
    }
    return count;
}