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
typedef  int /*<<< orphan*/  uint8_t ;
struct buffer {int offset; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BPTR (struct buffer*) ; 
 int /*<<< orphan*/  buf_valid (struct buffer*) ; 

__attribute__((used)) static inline uint8_t *
buf_prepend(struct buffer *buf, int size)
{
    if (!buf_valid(buf) || size < 0 || size > buf->offset)
    {
        return NULL;
    }
    buf->offset -= size;
    buf->len += size;
    return BPTR(buf);
}