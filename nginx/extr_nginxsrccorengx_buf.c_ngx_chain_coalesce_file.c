#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
typedef  scalar_t__ ngx_fd_t ;
struct TYPE_7__ {struct TYPE_7__* next; TYPE_2__* buf; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_6__ {scalar_t__ file_pos; scalar_t__ file_last; TYPE_1__* file; scalar_t__ in_file; } ;
struct TYPE_5__ {scalar_t__ fd; } ;

/* Variables and functions */
 scalar_t__ ngx_pagesize ; 

off_t
ngx_chain_coalesce_file(ngx_chain_t **in, off_t limit)
{
    off_t         total, size, aligned, fprev;
    ngx_fd_t      fd;
    ngx_chain_t  *cl;

    total = 0;

    cl = *in;
    fd = cl->buf->file->fd;

    do {
        size = cl->buf->file_last - cl->buf->file_pos;

        if (size > limit - total) {
            size = limit - total;

            aligned = (cl->buf->file_pos + size + ngx_pagesize - 1)
                       & ~((off_t) ngx_pagesize - 1);

            if (aligned <= cl->buf->file_last) {
                size = aligned - cl->buf->file_pos;
            }

            total += size;
            break;
        }

        total += size;
        fprev = cl->buf->file_pos + size;
        cl = cl->next;

    } while (cl
             && cl->buf->in_file
             && total < limit
             && fd == cl->buf->file->fd
             && fprev == cl->buf->file_pos);

    *in = cl;

    return total;
}