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
struct ra_buf_gl {int /*<<< orphan*/  target; int /*<<< orphan*/  buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_mutable; } ;
struct ra_buf {TYPE_1__ params; struct ra_buf_gl* priv; } ;
struct ra {int dummy; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BufferSubData ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void const*) ;} ;
typedef  TYPE_2__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* ra_gl_get (struct ra*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void const*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl_buf_update(struct ra *ra, struct ra_buf *buf, ptrdiff_t offset,
                          const void *data, size_t size)
{
    GL *gl = ra_gl_get(ra);
    struct ra_buf_gl *buf_gl = buf->priv;
    assert(buf->params.host_mutable);

    gl->BindBuffer(buf_gl->target, buf_gl->buffer);
    gl->BufferSubData(buf_gl->target, offset, size, data);
    gl->BindBuffer(buf_gl->target, 0);
}