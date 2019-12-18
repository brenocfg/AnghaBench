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
struct ra_buf_gl {int /*<<< orphan*/ * fence; } ;
struct ra_buf {struct ra_buf_gl* priv; int /*<<< orphan*/  data; } ;
struct ra {int dummy; } ;
struct TYPE_3__ {scalar_t__ (* ClientWaitSync ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteSync ) (int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 scalar_t__ GL_ALREADY_SIGNALED ; 
 TYPE_1__* ra_gl_get (struct ra*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gl_buf_poll(struct ra *ra, struct ra_buf *buf)
{
    // Non-persistently mapped buffers are always implicitly reusable in OpenGL,
    // the implementation will create more buffers under the hood if needed.
    if (!buf->data)
        return true;

    GL *gl = ra_gl_get(ra);
    struct ra_buf_gl *buf_gl = buf->priv;

    if (buf_gl->fence) {
        GLenum res = gl->ClientWaitSync(buf_gl->fence, 0, 0); // non-blocking
        if (res == GL_ALREADY_SIGNALED) {
            gl->DeleteSync(buf_gl->fence);
            buf_gl->fence = NULL;
        }
    }

    return !buf_gl->fence;
}