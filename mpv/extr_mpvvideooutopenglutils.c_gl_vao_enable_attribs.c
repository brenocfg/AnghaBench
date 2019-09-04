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
struct ra_renderpass_input {int type; int dim_m; scalar_t__ offset; int /*<<< orphan*/  dim_v; } ;
struct gl_vao {int num_entries; int /*<<< orphan*/  stride; struct ra_renderpass_input* entries; TYPE_1__* gl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* VertexAttribPointer ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* EnableVertexAttribArray ) (int) ;} ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_INT ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
#define  RA_VARTYPE_BYTE_UNORM 130 
#define  RA_VARTYPE_FLOAT 129 
#define  RA_VARTYPE_INT 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void gl_vao_enable_attribs(struct gl_vao *vao)
{
    GL *gl = vao->gl;

    for (int n = 0; n < vao->num_entries; n++) {
        const struct ra_renderpass_input *e = &vao->entries[n];
        GLenum type = 0;
        bool normalized = false;
        switch (e->type) {
        case RA_VARTYPE_INT:
            type = GL_INT;
            break;
        case RA_VARTYPE_FLOAT:
            type = GL_FLOAT;
            break;
        case RA_VARTYPE_BYTE_UNORM:
            type = GL_UNSIGNED_BYTE;
            normalized = true;
            break;
        default:
            abort();
        }
        assert(e->dim_m == 1);

        gl->EnableVertexAttribArray(n);
        gl->VertexAttribPointer(n, e->dim_v, type, normalized,
                                vao->stride, (void *)(intptr_t)e->offset);
    }
}