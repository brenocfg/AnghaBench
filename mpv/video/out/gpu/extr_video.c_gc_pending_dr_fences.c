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
struct mp_image {int dummy; } ;
struct gl_video {int num_dr_buffers; TYPE_2__* ra; struct dr_buffer* dr_buffers; } ;
struct dr_buffer {struct mp_image* mpi; int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {TYPE_1__* fns; } ;
struct TYPE_3__ {int (* buf_poll ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

__attribute__((used)) static void gc_pending_dr_fences(struct gl_video *p, bool force)
{
again:;
    for (int n = 0; n < p->num_dr_buffers; n++) {
        struct dr_buffer *buffer = &p->dr_buffers[n];
        if (!buffer->mpi)
            continue;

        bool res = p->ra->fns->buf_poll(p->ra, buffer->buf);
        if (res || force) {
            // Unreferencing the image could cause gl_video_dr_free_buffer()
            // to be called by the talloc destructor (if it was the last
            // reference). This will implicitly invalidate the buffer pointer
            // and change the p->dr_buffers array. To make it worse, it could
            // free multiple dr_buffers due to weird theoretical corner cases.
            // This is also why we use the goto to iterate again from the
            // start, because everything gets fucked up. Hail satan!
            struct mp_image *ref = buffer->mpi;
            buffer->mpi = NULL;
            talloc_free(ref);
            goto again;
        }
    }
}