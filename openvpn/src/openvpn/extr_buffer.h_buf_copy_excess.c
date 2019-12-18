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
struct buffer {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_advance (struct buffer*,int) ; 
 int buf_copy (struct buffer*,struct buffer*) ; 

__attribute__((used)) static inline bool
buf_copy_excess(struct buffer *dest,
                struct buffer *src,
                int len)
{
    if (len < 0)
    {
        return false;
    }
    if (src->len > len)
    {
        struct buffer b = *src;
        src->len = len;
        if (!buf_advance(&b, len))
        {
            return false;
        }
        return buf_copy(dest, &b);
    }
    else
    {
        return true;
    }
}