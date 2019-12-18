#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ buf_cur; scalar_t__ buf_end; int buffer_mask; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int ring_copy (TYPE_1__*,void*,int,scalar_t__) ; 
 int /*<<< orphan*/  stream_drop_buffers (TYPE_1__*) ; 
 int /*<<< orphan*/  stream_read_more (TYPE_1__*,int) ; 
 int stream_read_unbuffered (TYPE_1__*,void*,int) ; 

int stream_read_partial(stream_t *s, void *buf, int buf_size)
{
    assert(s->buf_cur <= s->buf_end);
    assert(buf_size >= 0);
    if (s->buf_cur == s->buf_end && buf_size > 0) {
        if (buf_size > (s->buffer_mask + 1) / 2) {
            // Direct read if the buffer is too small anyway.
            stream_drop_buffers(s);
            return stream_read_unbuffered(s, buf, buf_size);
        }
        stream_read_more(s, 1);
    }
    int res = ring_copy(s, buf, buf_size, s->buf_cur);
    s->buf_cur += res;
    return res;
}