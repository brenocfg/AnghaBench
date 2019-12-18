#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nk_font_atlas {int dummy; } ;
struct nk_font {int /*<<< orphan*/  handle; } ;
struct nk_context {int dummy; } ;
struct nk_canvas {int /*<<< orphan*/  painter; } ;
struct device {int /*<<< orphan*/  null; scalar_t__ font_tex; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 scalar_t__ GLEW_OK ; 
 int /*<<< orphan*/  GLFW_CONTEXT_VERSION_MAJOR ; 
 int /*<<< orphan*/  GLFW_CONTEXT_VERSION_MINOR ; 
 int GLFW_OPENGL_CORE_PROFILE ; 
 int /*<<< orphan*/  GLFW_OPENGL_FORWARD_COMPAT ; 
 int /*<<< orphan*/  GLFW_OPENGL_PROFILE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  NK_ANTI_ALIASING_ON ; 
 int /*<<< orphan*/  NK_FONT_ATLAS_RGBA32 ; 
 int WINDOW_HEIGHT ; 
 int WINDOW_WIDTH ; 
 int /*<<< orphan*/  canvas_begin (struct nk_context*,struct nk_canvas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canvas_end (struct nk_context*,struct nk_canvas*) ; 
 int /*<<< orphan*/  device_draw (struct device*,struct nk_context*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init (struct device*) ; 
 int /*<<< orphan*/  device_shutdown (struct device*) ; 
 int /*<<< orphan*/  device_upload_atlas (struct device*,void const*,int,int) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int glewExperimental ; 
 scalar_t__ glewInit () ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetCharCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetScrollCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowUserPointer (int /*<<< orphan*/ *,struct nk_context*) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_draw_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_fill_arc (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_fill_circle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_fill_polygon (int /*<<< orphan*/ ,float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_fill_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_fill_triangle (int /*<<< orphan*/ ,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 struct nk_font* nk_font_atlas_add_default (struct nk_font_atlas*,int,int /*<<< orphan*/ ) ; 
 void* nk_font_atlas_bake (struct nk_font_atlas*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_font_atlas_begin (struct nk_font_atlas*) ; 
 int /*<<< orphan*/  nk_font_atlas_clear (struct nk_font_atlas*) ; 
 int /*<<< orphan*/  nk_font_atlas_end (struct nk_font_atlas*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_font_atlas_init_default (struct nk_font_atlas*) ; 
 int /*<<< orphan*/  nk_free (struct nk_context*) ; 
 int /*<<< orphan*/  nk_handle_id (int) ; 
 int /*<<< orphan*/  nk_init_default (struct nk_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 int /*<<< orphan*/  nk_rgb (int,int,int) ; 
 int /*<<< orphan*/  nk_stroke_circle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_stroke_curve (int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_stroke_line (int /*<<< orphan*/ ,int,int,int,int,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_stroke_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_stroke_triangle (int /*<<< orphan*/ ,int,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pump_input (struct nk_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scroll_input ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  text_input ; 

int main(int argc, char *argv[])
{
    /* Platform */
    static GLFWwindow *win;
    int width = 0, height = 0;

    /* GUI */
    struct device device;
    struct nk_font_atlas atlas;
    struct nk_context ctx;

    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stdout, "[GFLW] failed to init!\n");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo", NULL, NULL);
    glfwMakeContextCurrent(win);
    glfwSetWindowUserPointer(win, &ctx);
    glfwSetCharCallback(win, text_input);
    glfwSetScrollCallback(win, scroll_input);
    glfwGetWindowSize(win, &width, &height);

    /* OpenGL */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to setup GLEW\n");
        exit(1);
    }

    /* GUI */
    {device_init(&device);
    {const void *image; int w, h;
    struct nk_font *font;
    nk_font_atlas_init_default(&atlas);
    nk_font_atlas_begin(&atlas);
    font = nk_font_atlas_add_default(&atlas, 13, 0);
    image = nk_font_atlas_bake(&atlas, &w, &h, NK_FONT_ATLAS_RGBA32);
    device_upload_atlas(&device, image, w, h);
    nk_font_atlas_end(&atlas, nk_handle_id((int)device.font_tex), &device.null);
    nk_init_default(&ctx, &font->handle);

    glEnable(GL_TEXTURE_2D);
    while (!glfwWindowShouldClose(win))
    {
        /* input */
        pump_input(&ctx, win);

        /* draw */
        {struct nk_canvas canvas;
        canvas_begin(&ctx, &canvas, 0, 0, 0, width, height, nk_rgb(250,250,250));
        {
            nk_fill_rect(canvas.painter, nk_rect(15,15,210,210), 5, nk_rgb(247, 230, 154));
            nk_fill_rect(canvas.painter, nk_rect(20,20,200,200), 5, nk_rgb(188, 174, 118));
            nk_draw_text(canvas.painter, nk_rect(30, 30, 150, 20), "Text to draw", 12, &font->handle, nk_rgb(188,174,118), nk_rgb(0,0,0));
            nk_fill_rect(canvas.painter, nk_rect(250,20,100,100), 0, nk_rgb(0,0,255));
            nk_fill_circle(canvas.painter, nk_rect(20,250,100,100), nk_rgb(255,0,0));
            nk_fill_triangle(canvas.painter, 250, 250, 350, 250, 300, 350, nk_rgb(0,255,0));
            nk_fill_arc(canvas.painter, 300, 180, 50, 0, 3.141592654f * 3.0f / 4.0f, nk_rgb(255,255,0));

            {float points[12];
            points[0] = 200; points[1] = 250;
            points[2] = 250; points[3] = 350;
            points[4] = 225; points[5] = 350;
            points[6] = 200; points[7] = 300;
            points[8] = 175; points[9] = 350;
            points[10] = 150; points[11] = 350;
            nk_fill_polygon(canvas.painter, points, 6, nk_rgb(0,0,0));}

            nk_stroke_line(canvas.painter, 15, 10, 200, 10, 2.0f, nk_rgb(189,45,75));
            nk_stroke_rect(canvas.painter, nk_rect(370, 20, 100, 100), 10, 3, nk_rgb(0,0,255));
            nk_stroke_curve(canvas.painter, 380, 200, 405, 270, 455, 120, 480, 200, 2, nk_rgb(0,150,220));
            nk_stroke_circle(canvas.painter, nk_rect(20, 370, 100, 100), 5, nk_rgb(0,255,120));
            nk_stroke_triangle(canvas.painter, 370, 250, 470, 250, 420, 350, 6, nk_rgb(255,0,143));
        }
        canvas_end(&ctx, &canvas);}

        /* Draw */
        glfwGetWindowSize(win, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        device_draw(&device, &ctx, width, height, NK_ANTI_ALIASING_ON);
        glfwSwapBuffers(win);
    }}}
    nk_font_atlas_clear(&atlas);
    nk_free(&ctx);
    device_shutdown(&device);
    glfwTerminate();
    return 0;
}