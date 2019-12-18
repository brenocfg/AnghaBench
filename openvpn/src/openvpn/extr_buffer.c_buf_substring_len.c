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
struct buffer {int dummy; } ;

/* Variables and functions */
 int buf_read_u8 (struct buffer*) ; 

int
buf_substring_len(const struct buffer *buf, int delim)
{
    int i = 0;
    struct buffer tmp = *buf;
    int c;

    while ((c = buf_read_u8(&tmp)) >= 0)
    {
        ++i;
        if (c == delim)
        {
            return i;
        }
    }
    return -1;
}