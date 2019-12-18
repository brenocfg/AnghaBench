#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ra_buf_gl {int /*<<< orphan*/  buffer; int /*<<< orphan*/  target; scalar_t__ data; scalar_t__ fence; struct ra_buf_gl* priv; } ;
struct ra_buf {int /*<<< orphan*/  buffer; int /*<<< orphan*/  target; scalar_t__ data; scalar_t__ fence; struct ra_buf* priv; } ;
struct ra {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DeleteBuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* UnmapBuffer ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteSync ) (scalar_t__) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 TYPE_1__* ra_gl_get (struct ra*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct ra_buf_gl*) ; 

__attribute__((used)) static void gl_buf_destroy(struct ra *ra, struct ra_buf *buf)
{
    if (!buf)
        return;

    GL *gl = ra_gl_get(ra);
    struct ra_buf_gl *buf_gl = buf->priv;

    if (buf_gl->fence)
        gl->DeleteSync(buf_gl->fence);

    if (buf->data) {
        gl->BindBuffer(buf_gl->target, buf_gl->buffer);
        gl->UnmapBuffer(buf_gl->target);
        gl->BindBuffer(buf_gl->target, 0);
    }
    gl->DeleteBuffers(1, &buf_gl->buffer);

    talloc_free(buf_gl);
    talloc_free(buf);
}