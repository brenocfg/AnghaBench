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
struct gl_vao {int num_entries; TYPE_1__* gl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* DisableVertexAttribArray ) (int) ;int /*<<< orphan*/  (* BindVertexArray ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static void gl_vao_unbind(struct gl_vao *vao)
{
    GL *gl = vao->gl;

    if (gl->BindVertexArray) {
        gl->BindVertexArray(0);
    } else {
        for (int n = 0; n < vao->num_entries; n++)
            gl->DisableVertexAttribArray(n);
    }
}