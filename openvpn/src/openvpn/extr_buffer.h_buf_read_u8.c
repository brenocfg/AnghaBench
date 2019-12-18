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
 int BLEN (struct buffer*) ; 
 int* BPTR (struct buffer*) ; 
 int /*<<< orphan*/  buf_advance (struct buffer*,int) ; 

__attribute__((used)) static inline int
buf_read_u8(struct buffer *buf)
{
    int ret;
    if (BLEN(buf) < 1)
    {
        return -1;
    }
    ret = *BPTR(buf);
    buf_advance(buf, 1);
    return ret;
}