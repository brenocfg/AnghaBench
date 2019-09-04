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
struct gl_vao {size_t stride; int /*<<< orphan*/  buffer; TYPE_1__* gl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* DrawArrays ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BufferData ) (int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_STREAM_DRAW ; 
 int /*<<< orphan*/  gl_vao_bind (struct gl_vao*) ; 
 int /*<<< orphan*/  gl_vao_unbind (struct gl_vao*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void gl_vao_draw_data(struct gl_vao *vao, GLenum prim, void *ptr, size_t num)
{
    GL *gl = vao->gl;

    if (ptr) {
        gl->BindBuffer(GL_ARRAY_BUFFER, vao->buffer);
        gl->BufferData(GL_ARRAY_BUFFER, num * vao->stride, ptr, GL_STREAM_DRAW);
        gl->BindBuffer(GL_ARRAY_BUFFER, 0);
    }

    gl_vao_bind(vao);

    gl->DrawArrays(prim, 0, num);

    gl_vao_unbind(vao);
}