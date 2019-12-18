#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_file_t ;
struct TYPE_5__ {struct TYPE_5__* next; TYPE_1__* buf; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_4__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ ngx_write_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

ssize_t
ngx_write_chain_to_file(ngx_file_t *file, ngx_chain_t *cl, off_t offset,
    ngx_pool_t *pool)
{
    u_char   *buf, *prev;
    size_t    size;
    ssize_t   total, n;

    total = 0;

    while (cl) {
        buf = cl->buf->pos;
        prev = buf;
        size = 0;

        /* coalesce the neighbouring bufs */

        while (cl && prev == cl->buf->pos) {
            size += cl->buf->last - cl->buf->pos;
            prev = cl->buf->last;
            cl = cl->next;
        }

        n = ngx_write_file(file, buf, size, offset);

        if (n == NGX_ERROR) {
            return NGX_ERROR;
        }

        total += n;
        offset += n;
    }

    return total;
}