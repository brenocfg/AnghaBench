#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct gl_video {int num_dr_buffers; struct dr_buffer* dr_buffers; int /*<<< orphan*/  ra; } ;
struct dr_buffer {TYPE_1__* buf; int /*<<< orphan*/  mpi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct dr_buffer*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ra_buf_free (int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static void gl_video_dr_free_buffer(void *opaque, uint8_t *data)
{
    struct gl_video *p = opaque;

    for (int n = 0; n < p->num_dr_buffers; n++) {
        struct dr_buffer *buffer = &p->dr_buffers[n];
        if (buffer->buf->data == data) {
            assert(!buffer->mpi); // can't be freed while it has a ref
            ra_buf_free(p->ra, &buffer->buf);
            MP_TARRAY_REMOVE_AT(p->dr_buffers, p->num_dr_buffers, n);
            return;
        }
    }
    // not found - must not happen
    assert(0);
}