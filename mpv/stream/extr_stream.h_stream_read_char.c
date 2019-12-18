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
struct TYPE_4__ {scalar_t__ buf_cur; scalar_t__ buf_end; int* buffer; size_t buffer_mask; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int stream_read_char_fallback (TYPE_1__*) ; 

__attribute__((used)) inline static int stream_read_char(stream_t *s)
{
    return s->buf_cur < s->buf_end
        ? s->buffer[(s->buf_cur++) & s->buffer_mask]
        : stream_read_char_fallback(s);
}