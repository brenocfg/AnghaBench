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
struct TYPE_5__ {int /*<<< orphan*/  buf_cur; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int ring_copy (TYPE_1__*,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stream_read_more (TYPE_1__*,int) ; 

int stream_read_peek(stream_t *s, void *buf, int buf_size)
{
    while (stream_read_more(s, buf_size)) {}
    return ring_copy(s, buf, buf_size, s->buf_cur);
}