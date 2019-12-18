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
 int /*<<< orphan*/  buf_safe_bidir (struct buffer*,int) ; 

__attribute__((used)) static inline bool
buf_inc_len(struct buffer *buf, int inc)
{
    if (!buf_safe_bidir(buf, inc))
    {
        return false;
    }
    buf->len += inc;
    return true;
}