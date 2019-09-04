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
struct ra_format {int num_components; scalar_t__* component_depth; struct gl_format* priv; } ;
struct gl_format {scalar_t__ format; int /*<<< orphan*/  type; int /*<<< orphan*/  internal_format; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DeleteTextures ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* GetTexLevelParameteriv ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,scalar_t__*) ;int /*<<< orphan*/  (* TexImage2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenTextures ) (int,int /*<<< orphan*/ *) ;scalar_t__ es; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 scalar_t__ GL_LUMINANCE ; 
 scalar_t__ GL_LUMINANCE_ALPHA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  const GL_TEXTURE_ALPHA_SIZE ; 
 int /*<<< orphan*/  const GL_TEXTURE_BLUE_SIZE ; 
 int /*<<< orphan*/  const GL_TEXTURE_GREEN_SIZE ; 
 int /*<<< orphan*/  const GL_TEXTURE_LUMINANCE_SIZE ; 
 int /*<<< orphan*/  const GL_TEXTURE_RED_SIZE ; 
 int MP_ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,scalar_t__*) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void probe_real_size(GL *gl, struct ra_format *fmt)
{
    const struct gl_format *gl_fmt = fmt->priv;

    if (!gl->GetTexLevelParameteriv)
        return; // GLES

    bool is_la = gl_fmt->format == GL_LUMINANCE ||
                 gl_fmt->format == GL_LUMINANCE_ALPHA;
    if (is_la && gl->es)
        return; // GLES doesn't provide GL_TEXTURE_LUMINANCE_SIZE.

    GLuint tex;
    gl->GenTextures(1, &tex);
    gl->BindTexture(GL_TEXTURE_2D, tex);
    gl->TexImage2D(GL_TEXTURE_2D, 0, gl_fmt->internal_format, 64, 64, 0,
                   gl_fmt->format, gl_fmt->type, NULL);
    for (int i = 0; i < fmt->num_components; i++) {
        const GLenum pnames[] = {
            GL_TEXTURE_RED_SIZE,
            GL_TEXTURE_GREEN_SIZE,
            GL_TEXTURE_BLUE_SIZE,
            GL_TEXTURE_ALPHA_SIZE,
            GL_TEXTURE_LUMINANCE_SIZE,
            GL_TEXTURE_ALPHA_SIZE,
        };
        int comp = is_la ? i + 4 : i;
        assert(comp < MP_ARRAY_SIZE(pnames));
        GLint param = -1;
        gl->GetTexLevelParameteriv(GL_TEXTURE_2D, 0, pnames[comp], &param);
        fmt->component_depth[i] = param > 0 ? param : 0;
    }
    gl->DeleteTextures(1, &tex);
}