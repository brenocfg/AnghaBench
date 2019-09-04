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
struct ra_tex_gl {int /*<<< orphan*/  texture; int /*<<< orphan*/  target; int /*<<< orphan*/  internal_format; } ;
struct TYPE_6__ {int storage_dst; int render_src; } ;
struct ra_tex {TYPE_2__ params; struct ra_tex_gl* priv; } ;
struct ra_renderpass_input_val {size_t index; float* data; } ;
struct ra_renderpass_input {int type; int dim_v; int dim_m; scalar_t__ binding; } ;
struct ra_renderpass_gl {size_t num_uniform_loc; int /*<<< orphan*/ * uniform_loc; } ;
struct TYPE_5__ {struct ra_renderpass_input* inputs; } ;
struct ra_renderpass {TYPE_1__ params; struct ra_renderpass_gl* priv; } ;
struct ra_buf_gl {int /*<<< orphan*/  target; int /*<<< orphan*/  buffer; } ;
struct ra_buf {struct ra_buf_gl* priv; } ;
struct ra {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* MemoryBarrier ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindBufferBase ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ActiveTexture ) (scalar_t__) ;int /*<<< orphan*/  (* BindImageTexture ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* UniformMatrix3fv ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ;int /*<<< orphan*/  (* UniformMatrix2fv ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ;int /*<<< orphan*/  (* Uniform4f ) (int /*<<< orphan*/ ,float,float,float,float) ;int /*<<< orphan*/  (* Uniform3f ) (int /*<<< orphan*/ ,float,float,float) ;int /*<<< orphan*/  (* Uniform2f ) (int /*<<< orphan*/ ,float,float) ;int /*<<< orphan*/  (* Uniform1f ) (int /*<<< orphan*/ ,float) ;int /*<<< orphan*/  (* Uniform1i ) (int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  GLint ;
typedef  TYPE_3__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_WRITE_ONLY ; 
#define  RA_VARTYPE_BUF_RO 133 
#define  RA_VARTYPE_BUF_RW 132 
#define  RA_VARTYPE_FLOAT 131 
#define  RA_VARTYPE_IMG_W 130 
#define  RA_VARTYPE_INT 129 
#define  RA_VARTYPE_TEX 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* ra_gl_get (struct ra*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,float,float,float) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,float,float,float,float) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  stub8 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (scalar_t__) ; 

__attribute__((used)) static void update_uniform(struct ra *ra, struct ra_renderpass *pass,
                           struct ra_renderpass_input_val *val)
{
    GL *gl = ra_gl_get(ra);
    struct ra_renderpass_gl *pass_gl = pass->priv;

    struct ra_renderpass_input *input = &pass->params.inputs[val->index];
    assert(val->index >= 0 && val->index < pass_gl->num_uniform_loc);
    GLint loc = pass_gl->uniform_loc[val->index];

    switch (input->type) {
    case RA_VARTYPE_INT: {
        assert(input->dim_v * input->dim_m == 1);
        if (loc < 0)
            break;
        gl->Uniform1i(loc, *(int *)val->data);
        break;
    }
    case RA_VARTYPE_FLOAT: {
        float *f = val->data;
        if (loc < 0)
            break;
        if (input->dim_m == 1) {
            switch (input->dim_v) {
            case 1: gl->Uniform1f(loc, f[0]); break;
            case 2: gl->Uniform2f(loc, f[0], f[1]); break;
            case 3: gl->Uniform3f(loc, f[0], f[1], f[2]); break;
            case 4: gl->Uniform4f(loc, f[0], f[1], f[2], f[3]); break;
            default: abort();
            }
        } else if (input->dim_v == 2 && input->dim_m == 2) {
            gl->UniformMatrix2fv(loc, 1, GL_FALSE, f);
        } else if (input->dim_v == 3 && input->dim_m == 3) {
            gl->UniformMatrix3fv(loc, 1, GL_FALSE, f);
        } else {
            abort();
        }
        break;
    }
    case RA_VARTYPE_IMG_W: {
        struct ra_tex *tex = *(struct ra_tex **)val->data;
        struct ra_tex_gl *tex_gl = tex->priv;
        assert(tex->params.storage_dst);
        gl->BindImageTexture(input->binding, tex_gl->texture, 0, GL_FALSE, 0,
                             GL_WRITE_ONLY, tex_gl->internal_format);
        break;
    }
    case RA_VARTYPE_TEX: {
        struct ra_tex *tex = *(struct ra_tex **)val->data;
        struct ra_tex_gl *tex_gl = tex->priv;
        assert(tex->params.render_src);
        gl->ActiveTexture(GL_TEXTURE0 + input->binding);
        gl->BindTexture(tex_gl->target, tex_gl->texture);
        break;
    }
    case RA_VARTYPE_BUF_RO: // fall through
    case RA_VARTYPE_BUF_RW: {
        struct ra_buf *buf = *(struct ra_buf **)val->data;
        struct ra_buf_gl *buf_gl = buf->priv;
        gl->BindBufferBase(buf_gl->target, input->binding, buf_gl->buffer);
        // SSBOs are not implicitly coherent in OpengL
        if (input->type == RA_VARTYPE_BUF_RW)
            gl->MemoryBarrier(buf_gl->target);
        break;
    }
    default:
        abort();
    }
}