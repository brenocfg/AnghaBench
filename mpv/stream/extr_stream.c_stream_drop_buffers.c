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
struct TYPE_5__ {scalar_t__ eof; scalar_t__ buf_end; scalar_t__ buf_cur; scalar_t__ buf_start; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  stream_resize_buffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_tell (TYPE_1__*) ; 

void stream_drop_buffers(stream_t *s)
{
    s->pos = stream_tell(s);
    s->buf_start = s->buf_cur = s->buf_end = 0;
    s->eof = 0;
    stream_resize_buffer(s, 0);
}