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
struct ra_tex_gl {int /*<<< orphan*/  internal_format; int /*<<< orphan*/  target; } ;
struct TYPE_6__ {int /*<<< orphan*/  render_src; } ;
struct ra_tex {TYPE_2__ params; struct ra_tex_gl* priv; } ;
struct ra_renderpass_input_val {size_t index; scalar_t__ data; } ;
struct ra_renderpass_input {int type; scalar_t__ binding; } ;
struct TYPE_5__ {struct ra_renderpass_input* inputs; } ;
struct ra_renderpass {TYPE_1__ params; } ;
struct ra {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* BindBufferBase ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindImageTexture ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ActiveTexture ) (scalar_t__) ;} ;
typedef  TYPE_3__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_SHADER_STORAGE_BUFFER ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_WRITE_ONLY ; 
#define  RA_VARTYPE_BUF_RW 130 
#define  RA_VARTYPE_IMG_W 129 
#define  RA_VARTYPE_TEX 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* ra_gl_get (struct ra*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_binding(struct ra *ra, struct ra_renderpass *pass,
                           struct ra_renderpass_input_val *val)
{
    GL *gl = ra_gl_get(ra);

    struct ra_renderpass_input *input = &pass->params.inputs[val->index];

    switch (input->type) {
    case RA_VARTYPE_IMG_W: /* fall  through */
    case RA_VARTYPE_TEX: {
        struct ra_tex *tex = *(struct ra_tex **)val->data;
        struct ra_tex_gl *tex_gl = tex->priv;
        assert(tex->params.render_src);
        if (input->type == RA_VARTYPE_TEX) {
            gl->ActiveTexture(GL_TEXTURE0 + input->binding);
            gl->BindTexture(tex_gl->target, 0);
        } else {
            gl->BindImageTexture(input->binding, 0, 0, GL_FALSE, 0,
                                 GL_WRITE_ONLY, tex_gl->internal_format);
        }
        break;
    }
    case RA_VARTYPE_BUF_RW:
        gl->BindBufferBase(GL_SHADER_STORAGE_BUFFER, input->binding, 0);
        break;
    }
}