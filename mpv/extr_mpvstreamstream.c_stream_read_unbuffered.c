#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* fill_buffer ) (TYPE_1__*,void*,int) ;int eof; int pos; int total_unbuffered_read_bytes; int /*<<< orphan*/  cancel; scalar_t__ buf_len; scalar_t__ buf_pos; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_cancel_test (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,void*,int) ; 

__attribute__((used)) static int stream_read_unbuffered(stream_t *s, void *buf, int len)
{
    int res = 0;
    s->buf_pos = s->buf_len = 0;
    // we will retry even if we already reached EOF previously.
    if (s->fill_buffer && !mp_cancel_test(s->cancel))
        res = s->fill_buffer(s, buf, len);
    if (res <= 0) {
        s->eof = 1;
        return 0;
    }
    // When reading succeeded we are obviously not at eof.
    s->eof = 0;
    s->pos += res;
    s->total_unbuffered_read_bytes += res;
    return res;
}