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
struct buffer {int len; scalar_t__ offset; scalar_t__ capacity; } ;

/* Variables and functions */
 scalar_t__ buf_size_valid_signed (int) ; 
 scalar_t__ buf_valid (struct buffer const*) ; 

__attribute__((used)) static inline bool
buf_safe_bidir(const struct buffer *buf, int len)
{
    if (buf_valid(buf) && buf_size_valid_signed(len))
    {
        const int newlen = buf->len + len;
        return newlen >= 0 && buf->offset + newlen <= buf->capacity;
    }
    else
    {
        return false;
    }
}