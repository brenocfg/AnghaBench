#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct gl_video {int num_dr_buffers; struct dr_buffer* dr_buffers; } ;
struct dr_buffer {TYPE_2__* buf; } ;
struct TYPE_3__ {size_t size; } ;
struct TYPE_4__ {TYPE_1__ params; int /*<<< orphan*/ * data; } ;

/* Variables and functions */

__attribute__((used)) static struct dr_buffer *gl_find_dr_buffer(struct gl_video *p, uint8_t *ptr)
{
   for (int i = 0; i < p->num_dr_buffers; i++) {
       struct dr_buffer *buffer = &p->dr_buffers[i];
        uint8_t *bufptr = buffer->buf->data;
        size_t size = buffer->buf->params.size;
        if (ptr >= bufptr && ptr < bufptr + size)
            return buffer;
    }

    return NULL;
}