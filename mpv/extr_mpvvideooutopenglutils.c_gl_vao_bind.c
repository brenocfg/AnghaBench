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
struct gl_vao {int /*<<< orphan*/  buffer; int /*<<< orphan*/  vao; TYPE_1__* gl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* BindBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindVertexArray ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  gl_vao_enable_attribs (struct gl_vao*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl_vao_bind(struct gl_vao *vao)
{
    GL *gl = vao->gl;

    if (gl->BindVertexArray) {
        gl->BindVertexArray(vao->vao);
    } else {
        gl->BindBuffer(GL_ARRAY_BUFFER, vao->buffer);
        gl_vao_enable_attribs(vao);
        gl->BindBuffer(GL_ARRAY_BUFFER, 0);
    }
}