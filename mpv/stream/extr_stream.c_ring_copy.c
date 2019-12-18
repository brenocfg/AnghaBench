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
struct stream {int buf_start; int buf_end; int buffer_mask; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int MPMIN (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ring_copy(struct stream *s, void *dst, int len, int pos)
{
    assert(len >= 0);

    if (pos < s->buf_start || pos > s->buf_end)
        return 0;

    int copied = 0;
    len = MPMIN(len, s->buf_end - pos);

    if (len && pos <= s->buffer_mask) {
        int copy = MPMIN(len, s->buffer_mask + 1 - pos);
        memcpy(dst, &s->buffer[pos], copy);
        copied += copy;
        len -= copy;
        pos += copy;
    }

    if (len) {
        memcpy((char *)dst + copied, &s->buffer[pos & s->buffer_mask], len);
        copied += len;
    }

    return copied;
}