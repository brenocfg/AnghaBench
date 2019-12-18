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
 scalar_t__ buf_valid (struct buffer const*) ; 

__attribute__((used)) static int
buf_len(const struct buffer *buf)
{
    if (buf_valid(buf))
    {
        return buf->len;
    }
    else
    {
        return 0;
    }
}