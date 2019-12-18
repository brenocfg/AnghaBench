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
typedef  int uint32_t ;
struct stream {int buf_end; int buf_cur; int requested_buffer_size; int buffer_mask; void* buffer; int /*<<< orphan*/  buf_start; } ;

/* Variables and functions */
 int INT_MAX ; 
 int MPMAX (int,int) ; 
 int /*<<< orphan*/  MP_DBG (struct stream*,char*,int) ; 
 int STREAM_MIN_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int mp_round_next_power_of_2 (int) ; 
 int ring_copy (struct stream*,void*,int,int /*<<< orphan*/ ) ; 
 void* ta_alloc_size (struct stream*,int) ; 
 int /*<<< orphan*/  ta_free (void*) ; 

__attribute__((used)) static bool stream_resize_buffer(struct stream *s, uint32_t new)
{
    // Keep all valid buffer.
    int old_used_len = s->buf_end - s->buf_start;
    int old_pos = s->buf_cur - s->buf_start;
    new = MPMAX(new, old_used_len);

    new = MPMAX(new, s->requested_buffer_size);

    // This much is always required.
    new = MPMAX(new, STREAM_MIN_BUFFER_SIZE);

    new = mp_round_next_power_of_2(new);
    if (!new || new > INT_MAX / 8)
        return false;

    if (new == s->buffer_mask + 1)
        return true;

    MP_DBG(s, "resize stream to %d bytes\n", new);

    void *nbuf = ta_alloc_size(s, new);
    if (!nbuf)
        return false; // oom; tolerate it, caller needs to check if required

    int new_len = 0;
    if (s->buffer)
        new_len = ring_copy(s, nbuf, new, s->buf_start);
    assert(new_len == old_used_len);
    assert(old_pos <= old_used_len);
    s->buf_start = 0;
    s->buf_cur = old_pos;
    s->buf_end = new_len;

    ta_free(s->buffer);

    s->buffer = nbuf;
    s->buffer_mask = new - 1;

    return true;
}