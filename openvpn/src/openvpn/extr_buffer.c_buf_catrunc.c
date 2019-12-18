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
struct buffer {int data; int capacity; } ;

/* Variables and functions */
 int buf_forward_capacity (struct buffer*) ; 
 int buf_forward_capacity_total (struct buffer*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpynt (char*,char const*,int) ; 

void
buf_catrunc(struct buffer *buf, const char *str)
{
    if (buf_forward_capacity(buf) <= 1)
    {
        int len = (int) strlen(str) + 1;
        if (len < buf_forward_capacity_total(buf))
        {
            strncpynt((char *)(buf->data + buf->capacity - len), str, len);
        }
    }
}