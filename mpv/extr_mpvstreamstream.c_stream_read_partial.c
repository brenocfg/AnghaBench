#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t buf_pos; size_t buf_len; scalar_t__ eof; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  sector_size; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int FFMIN (int,size_t) ; 
 int STREAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stream_fill_buffer (TYPE_1__*) ; 
 int stream_read_unbuffered (TYPE_1__*,char*,int) ; 

int stream_read_partial(stream_t *s, char *buf, int buf_size)
{
    assert(s->buf_pos <= s->buf_len);
    assert(buf_size >= 0);
    if (s->buf_pos == s->buf_len && buf_size > 0) {
        s->buf_pos = s->buf_len = 0;
        // Do a direct read, but only if there's no sector alignment requirement
        // Also, small reads will be more efficient with buffering & copying
        if (!s->sector_size && buf_size >= STREAM_BUFFER_SIZE)
            return stream_read_unbuffered(s, buf, buf_size);
        if (!stream_fill_buffer(s))
            return 0;
    }
    int len = FFMIN(buf_size, s->buf_len - s->buf_pos);
    memcpy(buf, &s->buffer[s->buf_pos], len);
    s->buf_pos += len;
    if (len > 0)
        s->eof = 0;
    return len;
}