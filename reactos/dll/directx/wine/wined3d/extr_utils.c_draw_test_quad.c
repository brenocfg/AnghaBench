#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_vec3 {float member_0; float member_1; float member_2; int /*<<< orphan*/  x; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* p_glDrawArrays ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* p_glEnd ) () ;int /*<<< orphan*/  (* p_glVertex3fv ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glColor4f ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glBegin ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glLoadIdentity ) () ;int /*<<< orphan*/  (* p_glMatrixMode ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {scalar_t__ glsl_version; TYPE_2__ gl_ops; int /*<<< orphan*/ * supported; } ;
struct wined3d_color {int /*<<< orphan*/  a; int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct wined3d_caps_gl_ctx {void* test_program_id; int /*<<< orphan*/  test_vbo; struct wined3d_gl_info* gl_info; } ;
typedef  void* GLuint ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARB_FRAGMENT_SHADER ; 
 size_t ARB_VERTEX_BUFFER_OBJECT ; 
 size_t ARB_VERTEX_SHADER ; 
 int FALSE ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 void* GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_STREAM_DRAW ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 scalar_t__ MAKEDWORD_VERSION (int,int) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glAttachShader (void*,void*) ; 
 int /*<<< orphan*/  glBindAttribLocation (void*,int,char*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindFragDataLocation (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,struct wined3d_vec3 const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCompileShader (void*) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteShader (void*) ; 
 int /*<<< orphan*/  glDisableVertexAttribArray (int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glLinkProgram (void*) ; 
 int /*<<< orphan*/  glShaderSource (void*,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUseProgram (void*) ; 
 int /*<<< orphan*/  glVertexAttrib4f (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_glsl_info_log (struct wined3d_gl_info const*,void*,int) ; 
 int /*<<< orphan*/  shader_glsl_validate_link (struct wined3d_gl_info const*,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 () ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 () ; 

__attribute__((used)) static void draw_test_quad(struct wined3d_caps_gl_ctx *ctx, const struct wined3d_vec3 *geometry,
        const struct wined3d_color *color)
{
    const struct wined3d_gl_info *gl_info = ctx->gl_info;
    static const struct wined3d_vec3 default_geometry[] =
    {
        {-1.0f, -1.0f, 0.0f},
        { 1.0f, -1.0f, 0.0f},
        {-1.0f,  1.0f, 0.0f},
        { 1.0f,  1.0f, 0.0f},
    };
    static const char vs_core_header[] =
        "#version 150\n"
        "in vec4 pos;\n"
        "in vec4 color;\n"
        "out vec4 out_color;\n"
        "\n";
    static const char vs_legacy_header[] =
        "#version 120\n"
        "attribute vec4 pos;\n"
        "attribute vec4 color;\n"
        "varying vec4 out_color;\n"
        "\n";
    static const char vs_body[] =
        "void main()\n"
        "{\n"
        "    gl_Position = pos;\n"
        "    out_color = color;\n"
        "}\n";
    static const char fs_core[] =
        "#version 150\n"
        "in vec4 out_color;\n"
        "out vec4 fragment_color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    fragment_color = out_color;\n"
        "}\n";
    static const char fs_legacy[] =
        "#version 120\n"
        "varying vec4 out_color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_FragData[0] = out_color;\n"
        "}\n";
    const char *source[2];
    GLuint vs_id, fs_id;
    unsigned int i;

    if (!geometry)
        geometry = default_geometry;

    if (!gl_info->supported[ARB_VERTEX_BUFFER_OBJECT] || !gl_info->supported[ARB_VERTEX_SHADER]
            || !gl_info->supported[ARB_FRAGMENT_SHADER])
    {
        gl_info->gl_ops.gl.p_glDisable(GL_LIGHTING);
        gl_info->gl_ops.gl.p_glMatrixMode(GL_MODELVIEW);
        gl_info->gl_ops.gl.p_glLoadIdentity();
        gl_info->gl_ops.gl.p_glMatrixMode(GL_PROJECTION);
        gl_info->gl_ops.gl.p_glLoadIdentity();

        gl_info->gl_ops.gl.p_glBegin(GL_TRIANGLE_STRIP);
        gl_info->gl_ops.gl.p_glColor4f(color->r, color->g, color->b, color->a);
        for (i = 0; i < 4; ++i)
            gl_info->gl_ops.gl.p_glVertex3fv(&geometry[i].x);
        gl_info->gl_ops.gl.p_glEnd();
        checkGLcall("draw quad");
        return;
    }

    if (!ctx->test_vbo)
        GL_EXTCALL(glGenBuffers(1, &ctx->test_vbo));
    GL_EXTCALL(glBindBuffer(GL_ARRAY_BUFFER, ctx->test_vbo));
    GL_EXTCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(struct wined3d_vec3) * 4, geometry, GL_STREAM_DRAW));
    GL_EXTCALL(glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, 0, NULL));
    GL_EXTCALL(glVertexAttrib4f(1, color->r, color->g, color->b, color->a));
    GL_EXTCALL(glEnableVertexAttribArray(0));
    GL_EXTCALL(glDisableVertexAttribArray(1));

    if (!ctx->test_program_id)
    {
#ifdef __REACTOS__
        /* workaround CORE-15408 crash for many 3D applications.
           VBoxDisp with enabled 3D acceleration only supports OpenGL 2.1 (GLSL 120).
           Wine must not use shaders for OpenGL 3.2 (GLSL 150). */
        BOOL use_glsl_150 = FALSE;
#else
        BOOL use_glsl_150 = gl_info->glsl_version >= MAKEDWORD_VERSION(1, 50);
#endif

        ctx->test_program_id = GL_EXTCALL(glCreateProgram());

        vs_id = GL_EXTCALL(glCreateShader(GL_VERTEX_SHADER));
        source[0] = use_glsl_150 ? vs_core_header : vs_legacy_header;
        source[1] = vs_body;
        GL_EXTCALL(glShaderSource(vs_id, 2, source, NULL));
        GL_EXTCALL(glAttachShader(ctx->test_program_id, vs_id));
        GL_EXTCALL(glDeleteShader(vs_id));

        fs_id = GL_EXTCALL(glCreateShader(GL_FRAGMENT_SHADER));
        source[0] = use_glsl_150 ? fs_core : fs_legacy;
        GL_EXTCALL(glShaderSource(fs_id, 1, source, NULL));
        GL_EXTCALL(glAttachShader(ctx->test_program_id, fs_id));
        GL_EXTCALL(glDeleteShader(fs_id));

        GL_EXTCALL(glBindAttribLocation(ctx->test_program_id, 0, "pos"));
        GL_EXTCALL(glBindAttribLocation(ctx->test_program_id, 1, "color"));

        if (use_glsl_150)
            GL_EXTCALL(glBindFragDataLocation(ctx->test_program_id, 0, "fragment_color"));

        GL_EXTCALL(glCompileShader(vs_id));
        print_glsl_info_log(gl_info, vs_id, FALSE);
        GL_EXTCALL(glCompileShader(fs_id));
        print_glsl_info_log(gl_info, fs_id, FALSE);
        GL_EXTCALL(glLinkProgram(ctx->test_program_id));
        shader_glsl_validate_link(gl_info, ctx->test_program_id);
    }
    GL_EXTCALL(glUseProgram(ctx->test_program_id));

    gl_info->gl_ops.gl.p_glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    GL_EXTCALL(glUseProgram(0));
    GL_EXTCALL(glDisableVertexAttribArray(0));
    GL_EXTCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    checkGLcall("draw quad");
}