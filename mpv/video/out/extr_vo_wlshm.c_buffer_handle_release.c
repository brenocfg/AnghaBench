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
struct wl_buffer {int dummy; } ;
struct vo {scalar_t__ dwidth; scalar_t__ dheight; struct priv* priv; } ;
struct priv {struct buffer* free_buffers; } ;
struct TYPE_2__ {scalar_t__ w; scalar_t__ h; } ;
struct buffer {struct buffer* next; TYPE_1__ mpi; struct vo* vo; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (struct buffer*) ; 

__attribute__((used)) static void buffer_handle_release(void *data, struct wl_buffer *wl_buffer)
{
    struct buffer *buf = data;
    struct vo *vo = buf->vo;
    struct priv *p = vo->priv;

    if (buf->mpi.w == vo->dwidth && buf->mpi.h == vo->dheight) {
        buf->next = p->free_buffers;
        p->free_buffers = buf;
    } else {
        talloc_free(buf);
    }
}