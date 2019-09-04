#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_9__ ;
typedef  struct TYPE_49__   TYPE_8__ ;
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_25__ ;
typedef  struct TYPE_41__   TYPE_24__ ;
typedef  struct TYPE_40__   TYPE_23__ ;
typedef  struct TYPE_39__   TYPE_22__ ;
typedef  struct TYPE_38__   TYPE_21__ ;
typedef  struct TYPE_37__   TYPE_20__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_19__ ;
typedef  struct TYPE_34__   TYPE_18__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct nk_vec2 {float x; float y; } ;
struct nk_style_toggle {void* text_active; void* text_hover; void* text_normal; void* cursor_hover; void* cursor_normal; void* active; void* hover; void* normal; } ;
struct nk_panel {int dummy; } ;
struct nk_font_atlas {int dummy; } ;
struct nk_font {int /*<<< orphan*/  handle; } ;
struct TYPE_41__ {int border; void* selected_color; void* color; void* border_color; void* background; } ;
struct TYPE_39__ {void* selected_text_hover; void* selected_text_normal; void* selected_hover; void* selected_normal; void* text_active; void* text_hover; void* text_normal; void* cursor_text_hover; void* cursor_text_normal; void* cursor_hover; void* cursor_normal; void* border_color; void* active; void* hover; void* normal; } ;
struct TYPE_38__ {void* text_active; void* text_hover; void* text_normal; void* text_background; void* active; void* hover; void* normal; } ;
struct TYPE_40__ {int rounding; int border; TYPE_22__ edit; TYPE_21__ dec_button; TYPE_21__ inc_button; int /*<<< orphan*/  sym_right; int /*<<< orphan*/  sym_left; void* label_active; void* label_hover; void* label_normal; void* border_color; void* active; void* hover; void* normal; } ;
struct TYPE_37__ {int border; int rounding; void* selected_text_hover; void* selected_text_normal; void* selected_hover; void* selected_normal; void* text_active; void* text_hover; void* text_normal; void* cursor_text_hover; void* cursor_text_normal; void* cursor_hover; void* cursor_normal; void* border_color; void* active; void* hover; void* normal; } ;
struct TYPE_34__ {void* text_active; void* text_hover; void* text_normal; void* text_background; void* active; void* hover; void* normal; } ;
struct TYPE_35__ {int border; int rounding; TYPE_18__ button; void* label_active; void* label_hover; void* label_normal; void* border_color; void* active; void* hover; void* normal; } ;
struct TYPE_33__ {int border; int rounding; void* padding; void* border_color; void* cursor_active; void* cursor_hover; void* cursor_normal; void* active; void* hover; void* normal; } ;
struct TYPE_32__ {int bar_height; void* cursor_size; void* cursor_active; void* cursor_hover; void* cursor_normal; void* bar_filled; void* bar_active; void* bar_hover; void* bar_normal; void* active; void* hover; void* normal; } ;
struct TYPE_31__ {void* text_pressed_active; void* text_hover_active; void* text_normal_active; void* text_pressed; void* text_hover; void* text_normal; void* pressed_active; void* hover_active; void* normal_active; void* pressed; void* hover; void* normal; } ;
struct TYPE_29__ {void* text_active; void* text_hover; void* text_normal; void* text_background; void* active; void* hover; void* normal; } ;
struct TYPE_28__ {void* text_active; void* text_hover; void* text_normal; void* text_background; void* active; void* hover; void* normal; } ;
struct TYPE_27__ {void* text_active; void* text_hover; void* text_normal; void* text_background; void* active; void* hover; void* normal; } ;
struct TYPE_26__ {void* text_active; void* text_hover; void* text_normal; void* text_background; void* active; void* hover; void* normal; } ;
struct TYPE_30__ {TYPE_13__ node_maximize_button; TYPE_12__ node_minimize_button; TYPE_11__ tab_maximize_button; TYPE_10__ tab_minimize_button; void* text; } ;
struct TYPE_50__ {void* text_active; void* text_hover; void* text_normal; void* text_background; void* border_color; void* active; void* hover; void* normal; } ;
struct TYPE_49__ {void* text_active; void* text_hover; void* text_normal; void* text_background; void* border_color; void* active; void* hover; void* normal; } ;
struct TYPE_48__ {void* color; } ;
struct TYPE_47__ {void* text_active; void* text_hover; void* text_normal; void* text_background; void* border_color; void* active; void* hover; void* normal; } ;
struct TYPE_45__ {float border; void* text_active; void* text_hover; void* text_normal; void* text_background; void* border_color; void* active; void* hover; void* normal; } ;
struct TYPE_44__ {float border; void* text_active; void* text_hover; void* text_normal; void* text_background; void* border_color; void* active; void* hover; void* normal; } ;
struct TYPE_46__ {int border; int border_cursor; int rounding_cursor; TYPE_4__ dec_button; TYPE_3__ inc_button; scalar_t__ rounding; void* cursor_border_color; void* border_color; int /*<<< orphan*/  show_buttons; void* inc_symbol; void* dec_symbol; void* cursor_active; void* cursor_hover; void* cursor_normal; void* active; void* hover; void* normal; } ;
struct TYPE_36__ {void* label_active; void* label_hover; void* label_normal; void* active; void* hover; void* normal; } ;
struct TYPE_43__ {int border; TYPE_1__ header; void* padding; void* border_color; void* scrollbar_size; void* tooltip_border_color; void* group_border_color; void* menu_border_color; void* contextual_border_color; void* combo_border_color; void* fixed_background; void* background; } ;
struct TYPE_42__ {TYPE_24__ chart; TYPE_23__ property; TYPE_20__ edit; TYPE_19__ combo; TYPE_17__ progress; TYPE_16__ slider; TYPE_15__ selectable; TYPE_14__ tab; TYPE_9__ menu_button; TYPE_8__ contextual_button; TYPE_7__ text; TYPE_6__ button; struct nk_style_toggle option; struct nk_style_toggle checkbox; TYPE_5__ scrollv; TYPE_2__ window; } ;
struct nk_context {TYPE_25__ style; } ;
struct media {int /*<<< orphan*/  skin; void* slider_active; void* slider_hover; void* slider; void* tab_maximize; void* tab_minimize; void* button_active; void* button_hover; void* button; void* option_cursor; void* option; void* check_cursor; void* check; void* scrollbar_dec_button_hover; void* scrollbar_dec_button; void* scrollbar_inc_button_hover; void* scrollbar_inc_button; void* header; void* window; } ;
struct device {int /*<<< orphan*/  null; scalar_t__ font_tex; } ;
typedef  int nk_size ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 scalar_t__ GLEW_OK ; 
 int /*<<< orphan*/  GLFW_CONTEXT_VERSION_MAJOR ; 
 int /*<<< orphan*/  GLFW_CONTEXT_VERSION_MINOR ; 
 int /*<<< orphan*/  GLFW_KEY_BACKSPACE ; 
 int /*<<< orphan*/  GLFW_KEY_C ; 
 int /*<<< orphan*/  GLFW_KEY_DELETE ; 
 int /*<<< orphan*/  GLFW_KEY_DOWN ; 
 int /*<<< orphan*/  GLFW_KEY_E ; 
 int /*<<< orphan*/  GLFW_KEY_ENTER ; 
 int /*<<< orphan*/  GLFW_KEY_LEFT ; 
 int /*<<< orphan*/  GLFW_KEY_LEFT_CONTROL ; 
 int /*<<< orphan*/  GLFW_KEY_P ; 
 int /*<<< orphan*/  GLFW_KEY_RIGHT ; 
 int /*<<< orphan*/  GLFW_KEY_RIGHT_CONTROL ; 
 int /*<<< orphan*/  GLFW_KEY_TAB ; 
 int /*<<< orphan*/  GLFW_KEY_UP ; 
 int /*<<< orphan*/  GLFW_KEY_X ; 
 int /*<<< orphan*/  GLFW_MOUSE_BUTTON_LEFT ; 
 int /*<<< orphan*/  GLFW_MOUSE_BUTTON_MIDDLE ; 
 int /*<<< orphan*/  GLFW_MOUSE_BUTTON_RIGHT ; 
 int GLFW_OPENGL_CORE_PROFILE ; 
 int /*<<< orphan*/  GLFW_OPENGL_PROFILE ; 
 scalar_t__ GLFW_PRESS ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  LEN (char const**) ; 
 int /*<<< orphan*/  NK_ANTI_ALIASING_ON ; 
 int /*<<< orphan*/  NK_BUTTON_LEFT ; 
 int /*<<< orphan*/  NK_BUTTON_MIDDLE ; 
 int /*<<< orphan*/  NK_BUTTON_RIGHT ; 
 int /*<<< orphan*/  NK_CHART_LINES ; 
 int /*<<< orphan*/  NK_EDIT_FIELD ; 
 int /*<<< orphan*/  NK_FONT_ATLAS_RGBA32 ; 
 int /*<<< orphan*/  NK_KEY_BACKSPACE ; 
 int /*<<< orphan*/  NK_KEY_COPY ; 
 int /*<<< orphan*/  NK_KEY_CUT ; 
 int /*<<< orphan*/  NK_KEY_DEL ; 
 int /*<<< orphan*/  NK_KEY_DOWN ; 
 int /*<<< orphan*/  NK_KEY_ENTER ; 
 int /*<<< orphan*/  NK_KEY_LEFT ; 
 int /*<<< orphan*/  NK_KEY_PASTE ; 
 int /*<<< orphan*/  NK_KEY_RIGHT ; 
 int /*<<< orphan*/  NK_KEY_SHIFT ; 
 int /*<<< orphan*/  NK_KEY_TAB ; 
 int /*<<< orphan*/  NK_KEY_UP ; 
 int /*<<< orphan*/  NK_MAXIMIZED ; 
 int /*<<< orphan*/  NK_MODIFIABLE ; 
 void* NK_SYMBOL_NONE ; 
 int /*<<< orphan*/  NK_SYMBOL_TRIANGLE_LEFT ; 
 int /*<<< orphan*/  NK_SYMBOL_TRIANGLE_RIGHT ; 
 int /*<<< orphan*/  NK_TEXT_LEFT ; 
 int /*<<< orphan*/  NK_TREE_NODE ; 
 int NK_WINDOW_BORDER ; 
 int NK_WINDOW_MOVABLE ; 
 int NK_WINDOW_TITLE ; 
 int WINDOW_HEIGHT ; 
 int WINDOW_WIDTH ; 
 scalar_t__ cos (float) ; 
 int /*<<< orphan*/  device_draw (struct device*,struct nk_context*,int,int,struct nk_vec2,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init (struct device*) ; 
 int /*<<< orphan*/  device_shutdown (struct device*) ; 
 int /*<<< orphan*/  device_upload_atlas (struct device*,void const*,int,int) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fabs (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (double,double,double,float) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int glewExperimental ; 
 scalar_t__ glewInit () ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetCursorPos (int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ glfwGetKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ glfwGetMouseButton (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetCharCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetScrollCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowUserPointer (int /*<<< orphan*/ *,struct nk_context*) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  image_load (char*) ; 
 scalar_t__ nk_begin (struct nk_context*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nk_button_label (struct nk_context*,char*) ; 
 int /*<<< orphan*/  nk_chart_add_slot_colored (struct nk_context*,int /*<<< orphan*/ ,void*,void*,int,float,float) ; 
 scalar_t__ nk_chart_begin_colored (struct nk_context*,int /*<<< orphan*/ ,void*,void*,int,float,float) ; 
 int /*<<< orphan*/  nk_chart_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_chart_push_slot (struct nk_context*,float,int) ; 
 int /*<<< orphan*/  nk_check_label (struct nk_context*,char*,int) ; 
 int nk_combo (struct nk_context*,char const**,int /*<<< orphan*/ ,int,int,void*) ; 
 int /*<<< orphan*/  nk_edit_string (struct nk_context*,int /*<<< orphan*/ ,char*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_filter_default ; 
 struct nk_font* nk_font_atlas_add_default (struct nk_font_atlas*,float,int /*<<< orphan*/ *) ; 
 struct nk_font* nk_font_atlas_add_from_file (struct nk_font_atlas*,char const*,float,int /*<<< orphan*/ *) ; 
 void* nk_font_atlas_bake (struct nk_font_atlas*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_font_atlas_begin (struct nk_font_atlas*) ; 
 int /*<<< orphan*/  nk_font_atlas_clear (struct nk_font_atlas*) ; 
 int /*<<< orphan*/  nk_font_atlas_end (struct nk_font_atlas*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_font_atlas_init_default (struct nk_font_atlas*) ; 
 int /*<<< orphan*/  nk_free (struct nk_context*) ; 
 scalar_t__ nk_group_begin (struct nk_context*,char*,int) ; 
 int /*<<< orphan*/  nk_group_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_handle_id (int) ; 
 int /*<<< orphan*/  nk_init_default (struct nk_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_input_begin (struct nk_context*) ; 
 int /*<<< orphan*/  nk_input_button (struct nk_context*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  nk_input_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_input_key (struct nk_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_input_motion (struct nk_context*,int,int) ; 
 int /*<<< orphan*/  nk_label (struct nk_context*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_layout_row_dynamic (struct nk_context*,int,int) ; 
 int /*<<< orphan*/  nk_layout_row_static (struct nk_context*,int,int,int) ; 
 int /*<<< orphan*/  nk_option_label (struct nk_context*,char*,int) ; 
 int /*<<< orphan*/  nk_progress (struct nk_context*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_property_float (struct nk_context*,char*,float,float*,float,int,int) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 void* nk_rgb (int,int,int) ; 
 void* nk_rgba (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_selectable_label (struct nk_context*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nk_slider_int (struct nk_context*,int /*<<< orphan*/ ,int*,int,int) ; 
 void* nk_style_item_color (void*) ; 
 void* nk_style_item_hide () ; 
 void* nk_style_item_image (void*) ; 
 void* nk_subimage_id (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_tree_pop (struct nk_context*) ; 
 scalar_t__ nk_tree_push (struct nk_context*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_true ; 
 void* nk_vec2 (float,int) ; 
 float nk_widget_width (struct nk_context*) ; 
 int /*<<< orphan*/  scroll_input ; 
 scalar_t__ sin (float) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  text_input ; 

int main(int argc, char *argv[])
{
    /* Platform */
    static GLFWwindow *win;
    int width = 0, height = 0;
    int display_width=0, display_height=0;

    /* GUI */
    struct device device;
    struct nk_font_atlas atlas;
    struct media media;
    struct nk_context ctx;
    struct nk_font *font;

    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stdout, "[GFLW] failed to init!\n");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo", NULL, NULL);
    glfwMakeContextCurrent(win);
    glfwSetWindowUserPointer(win, &ctx);
    glfwSetCharCallback(win, text_input);
    glfwSetScrollCallback(win, scroll_input);
    glfwGetWindowSize(win, &width, &height);
    glfwGetFramebufferSize(win, &display_width, &display_height);

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
    const char *font_path = (argc > 1) ? argv[1]: 0;
    nk_font_atlas_init_default(&atlas);
    nk_font_atlas_begin(&atlas);
    if (font_path) font = nk_font_atlas_add_from_file(&atlas, font_path, 13.0f, NULL);
    else font = nk_font_atlas_add_default(&atlas, 13.0f, NULL);
    image = nk_font_atlas_bake(&atlas, &w, &h, NK_FONT_ATLAS_RGBA32);
    device_upload_atlas(&device, image, w, h);
    nk_font_atlas_end(&atlas, nk_handle_id((int)device.font_tex), &device.null);}
    nk_init_default(&ctx, &font->handle);}

    {   /* skin */
        glEnable(GL_TEXTURE_2D);
        media.skin = image_load("../skins/gwen.png");
        media.check = nk_subimage_id(media.skin, 512,512, nk_rect(464,32,15,15));
        media.check_cursor = nk_subimage_id(media.skin, 512,512, nk_rect(450,34,11,11));
        media.option = nk_subimage_id(media.skin, 512,512, nk_rect(464,64,15,15));
        media.option_cursor = nk_subimage_id(media.skin, 512,512, nk_rect(451,67,9,9));
        media.header = nk_subimage_id(media.skin, 512,512, nk_rect(128,0,127,24));
        media.window = nk_subimage_id(media.skin, 512,512, nk_rect(128,23,127,104));
        media.scrollbar_inc_button = nk_subimage_id(media.skin, 512,512, nk_rect(464,256,15,15));
        media.scrollbar_inc_button_hover = nk_subimage_id(media.skin, 512,512, nk_rect(464,320,15,15));
        media.scrollbar_dec_button = nk_subimage_id(media.skin, 512,512, nk_rect(464,224,15,15));
        media.scrollbar_dec_button_hover = nk_subimage_id(media.skin, 512,512, nk_rect(464,288,15,15));
        media.button = nk_subimage_id(media.skin, 512,512, nk_rect(384,336,127,31));
        media.button_hover = nk_subimage_id(media.skin, 512,512, nk_rect(384,368,127,31));
        media.button_active = nk_subimage_id(media.skin, 512,512, nk_rect(384,400,127,31));
        media.tab_minimize = nk_subimage_id(media.skin, 512,512, nk_rect(451, 99, 9, 9));
        media.tab_maximize = nk_subimage_id(media.skin, 512,512, nk_rect(467,99,9,9));
        media.slider = nk_subimage_id(media.skin, 512,512, nk_rect(418,33,11,14));
        media.slider_hover = nk_subimage_id(media.skin, 512,512, nk_rect(418,49,11,14));
        media.slider_active = nk_subimage_id(media.skin, 512,512, nk_rect(418,64,11,14));

        /* window */
        ctx.style.window.background = nk_rgb(204,204,204);
        ctx.style.window.fixed_background = nk_style_item_image(media.window);
        ctx.style.window.border_color = nk_rgb(67,67,67);
        ctx.style.window.combo_border_color = nk_rgb(67,67,67);
        ctx.style.window.contextual_border_color = nk_rgb(67,67,67);
        ctx.style.window.menu_border_color = nk_rgb(67,67,67);
        ctx.style.window.group_border_color = nk_rgb(67,67,67);
        ctx.style.window.tooltip_border_color = nk_rgb(67,67,67);
        ctx.style.window.scrollbar_size = nk_vec2(16,16);
        ctx.style.window.border_color = nk_rgba(0,0,0,0);
        ctx.style.window.padding = nk_vec2(8,4);
        ctx.style.window.border = 3;

        /* window header */
        ctx.style.window.header.normal = nk_style_item_image(media.header);
        ctx.style.window.header.hover = nk_style_item_image(media.header);
        ctx.style.window.header.active = nk_style_item_image(media.header);
        ctx.style.window.header.label_normal = nk_rgb(95,95,95);
        ctx.style.window.header.label_hover = nk_rgb(95,95,95);
        ctx.style.window.header.label_active = nk_rgb(95,95,95);

        /* scrollbar */
        ctx.style.scrollv.normal          = nk_style_item_color(nk_rgb(184,184,184));
        ctx.style.scrollv.hover           = nk_style_item_color(nk_rgb(184,184,184));
        ctx.style.scrollv.active          = nk_style_item_color(nk_rgb(184,184,184));
        ctx.style.scrollv.cursor_normal   = nk_style_item_color(nk_rgb(220,220,220));
        ctx.style.scrollv.cursor_hover    = nk_style_item_color(nk_rgb(235,235,235));
        ctx.style.scrollv.cursor_active   = nk_style_item_color(nk_rgb(99,202,255));
        ctx.style.scrollv.dec_symbol      = NK_SYMBOL_NONE;
        ctx.style.scrollv.inc_symbol      = NK_SYMBOL_NONE;
        ctx.style.scrollv.show_buttons    = nk_true;
        ctx.style.scrollv.border_color    = nk_rgb(81,81,81);
        ctx.style.scrollv.cursor_border_color = nk_rgb(81,81,81);
        ctx.style.scrollv.border          = 1;
        ctx.style.scrollv.rounding        = 0;
        ctx.style.scrollv.border_cursor   = 1;
        ctx.style.scrollv.rounding_cursor = 2;

        /* scrollbar buttons */
        ctx.style.scrollv.inc_button.normal          = nk_style_item_image(media.scrollbar_inc_button);
        ctx.style.scrollv.inc_button.hover           = nk_style_item_image(media.scrollbar_inc_button_hover);
        ctx.style.scrollv.inc_button.active          = nk_style_item_image(media.scrollbar_inc_button_hover);
        ctx.style.scrollv.inc_button.border_color    = nk_rgba(0,0,0,0);
        ctx.style.scrollv.inc_button.text_background = nk_rgba(0,0,0,0);
        ctx.style.scrollv.inc_button.text_normal     = nk_rgba(0,0,0,0);
        ctx.style.scrollv.inc_button.text_hover      = nk_rgba(0,0,0,0);
        ctx.style.scrollv.inc_button.text_active     = nk_rgba(0,0,0,0);
        ctx.style.scrollv.inc_button.border          = 0.0f;

        ctx.style.scrollv.dec_button.normal          = nk_style_item_image(media.scrollbar_dec_button);
        ctx.style.scrollv.dec_button.hover           = nk_style_item_image(media.scrollbar_dec_button_hover);
        ctx.style.scrollv.dec_button.active          = nk_style_item_image(media.scrollbar_dec_button_hover);
        ctx.style.scrollv.dec_button.border_color    = nk_rgba(0,0,0,0);
        ctx.style.scrollv.dec_button.text_background = nk_rgba(0,0,0,0);
        ctx.style.scrollv.dec_button.text_normal     = nk_rgba(0,0,0,0);
        ctx.style.scrollv.dec_button.text_hover      = nk_rgba(0,0,0,0);
        ctx.style.scrollv.dec_button.text_active     = nk_rgba(0,0,0,0);
        ctx.style.scrollv.dec_button.border          = 0.0f;

        /* checkbox toggle */
        {struct nk_style_toggle *toggle;
        toggle = &ctx.style.checkbox;
        toggle->normal          = nk_style_item_image(media.check);
        toggle->hover           = nk_style_item_image(media.check);
        toggle->active          = nk_style_item_image(media.check);
        toggle->cursor_normal   = nk_style_item_image(media.check_cursor);
        toggle->cursor_hover    = nk_style_item_image(media.check_cursor);
        toggle->text_normal     = nk_rgb(95,95,95);
        toggle->text_hover      = nk_rgb(95,95,95);
        toggle->text_active     = nk_rgb(95,95,95);}

        /* option toggle */
        {struct nk_style_toggle *toggle;
        toggle = &ctx.style.option;
        toggle->normal          = nk_style_item_image(media.option);
        toggle->hover           = nk_style_item_image(media.option);
        toggle->active          = nk_style_item_image(media.option);
        toggle->cursor_normal   = nk_style_item_image(media.option_cursor);
        toggle->cursor_hover    = nk_style_item_image(media.option_cursor);
        toggle->text_normal     = nk_rgb(95,95,95);
        toggle->text_hover      = nk_rgb(95,95,95);
        toggle->text_active     = nk_rgb(95,95,95);}

        /* default button */
        ctx.style.button.normal = nk_style_item_image(media.button);
        ctx.style.button.hover = nk_style_item_image(media.button_hover);
        ctx.style.button.active = nk_style_item_image(media.button_active);
        ctx.style.button.border_color = nk_rgba(0,0,0,0);
        ctx.style.button.text_background = nk_rgba(0,0,0,0);
        ctx.style.button.text_normal = nk_rgb(95,95,95);
        ctx.style.button.text_hover = nk_rgb(95,95,95);
        ctx.style.button.text_active = nk_rgb(95,95,95);

        /* default text */
        ctx.style.text.color = nk_rgb(95,95,95);

        /* contextual button */
        ctx.style.contextual_button.normal = nk_style_item_color(nk_rgb(206,206,206));
        ctx.style.contextual_button.hover = nk_style_item_color(nk_rgb(229,229,229));
        ctx.style.contextual_button.active = nk_style_item_color(nk_rgb(99,202,255));
        ctx.style.contextual_button.border_color = nk_rgba(0,0,0,0);
        ctx.style.contextual_button.text_background = nk_rgba(0,0,0,0);
        ctx.style.contextual_button.text_normal = nk_rgb(95,95,95);
        ctx.style.contextual_button.text_hover = nk_rgb(95,95,95);
        ctx.style.contextual_button.text_active = nk_rgb(95,95,95);

        /* menu button */
        ctx.style.menu_button.normal = nk_style_item_color(nk_rgb(206,206,206));
        ctx.style.menu_button.hover = nk_style_item_color(nk_rgb(229,229,229));
        ctx.style.menu_button.active = nk_style_item_color(nk_rgb(99,202,255));
        ctx.style.menu_button.border_color = nk_rgba(0,0,0,0);
        ctx.style.menu_button.text_background = nk_rgba(0,0,0,0);
        ctx.style.menu_button.text_normal = nk_rgb(95,95,95);
        ctx.style.menu_button.text_hover = nk_rgb(95,95,95);
        ctx.style.menu_button.text_active = nk_rgb(95,95,95);

        /* tree */
        ctx.style.tab.text = nk_rgb(95,95,95);
        ctx.style.tab.tab_minimize_button.normal = nk_style_item_image(media.tab_minimize);
        ctx.style.tab.tab_minimize_button.hover = nk_style_item_image(media.tab_minimize);
        ctx.style.tab.tab_minimize_button.active = nk_style_item_image(media.tab_minimize);
        ctx.style.tab.tab_minimize_button.text_background = nk_rgba(0,0,0,0);
        ctx.style.tab.tab_minimize_button.text_normal = nk_rgba(0,0,0,0);
        ctx.style.tab.tab_minimize_button.text_hover = nk_rgba(0,0,0,0);
        ctx.style.tab.tab_minimize_button.text_active = nk_rgba(0,0,0,0);

        ctx.style.tab.tab_maximize_button.normal = nk_style_item_image(media.tab_maximize);
        ctx.style.tab.tab_maximize_button.hover = nk_style_item_image(media.tab_maximize);
        ctx.style.tab.tab_maximize_button.active = nk_style_item_image(media.tab_maximize);
        ctx.style.tab.tab_maximize_button.text_background = nk_rgba(0,0,0,0);
        ctx.style.tab.tab_maximize_button.text_normal = nk_rgba(0,0,0,0);
        ctx.style.tab.tab_maximize_button.text_hover = nk_rgba(0,0,0,0);
        ctx.style.tab.tab_maximize_button.text_active = nk_rgba(0,0,0,0);

        ctx.style.tab.node_minimize_button.normal = nk_style_item_image(media.tab_minimize);
        ctx.style.tab.node_minimize_button.hover = nk_style_item_image(media.tab_minimize);
        ctx.style.tab.node_minimize_button.active = nk_style_item_image(media.tab_minimize);
        ctx.style.tab.node_minimize_button.text_background = nk_rgba(0,0,0,0);
        ctx.style.tab.node_minimize_button.text_normal = nk_rgba(0,0,0,0);
        ctx.style.tab.node_minimize_button.text_hover = nk_rgba(0,0,0,0);
        ctx.style.tab.node_minimize_button.text_active = nk_rgba(0,0,0,0);

        ctx.style.tab.node_maximize_button.normal = nk_style_item_image(media.tab_maximize);
        ctx.style.tab.node_maximize_button.hover = nk_style_item_image(media.tab_maximize);
        ctx.style.tab.node_maximize_button.active = nk_style_item_image(media.tab_maximize);
        ctx.style.tab.node_maximize_button.text_background = nk_rgba(0,0,0,0);
        ctx.style.tab.node_maximize_button.text_normal = nk_rgba(0,0,0,0);
        ctx.style.tab.node_maximize_button.text_hover = nk_rgba(0,0,0,0);
        ctx.style.tab.node_maximize_button.text_active = nk_rgba(0,0,0,0);

        /* selectable */
        ctx.style.selectable.normal = nk_style_item_color(nk_rgb(206,206,206));
        ctx.style.selectable.hover = nk_style_item_color(nk_rgb(206,206,206));
        ctx.style.selectable.pressed = nk_style_item_color(nk_rgb(206,206,206));
        ctx.style.selectable.normal_active = nk_style_item_color(nk_rgb(185,205,248));
        ctx.style.selectable.hover_active = nk_style_item_color(nk_rgb(185,205,248));
        ctx.style.selectable.pressed_active = nk_style_item_color(nk_rgb(185,205,248));
        ctx.style.selectable.text_normal = nk_rgb(95,95,95);
        ctx.style.selectable.text_hover = nk_rgb(95,95,95);
        ctx.style.selectable.text_pressed = nk_rgb(95,95,95);
        ctx.style.selectable.text_normal_active = nk_rgb(95,95,95);
        ctx.style.selectable.text_hover_active = nk_rgb(95,95,95);
        ctx.style.selectable.text_pressed_active = nk_rgb(95,95,95);

        /* slider */
        ctx.style.slider.normal          = nk_style_item_hide();
        ctx.style.slider.hover           = nk_style_item_hide();
        ctx.style.slider.active          = nk_style_item_hide();
        ctx.style.slider.bar_normal      = nk_rgb(156,156,156);
        ctx.style.slider.bar_hover       = nk_rgb(156,156,156);
        ctx.style.slider.bar_active      = nk_rgb(156,156,156);
        ctx.style.slider.bar_filled      = nk_rgb(156,156,156);
        ctx.style.slider.cursor_normal   = nk_style_item_image(media.slider);
        ctx.style.slider.cursor_hover    = nk_style_item_image(media.slider_hover);
        ctx.style.slider.cursor_active   = nk_style_item_image(media.slider_active);
        ctx.style.slider.cursor_size     = nk_vec2(16.5f,21);
        ctx.style.slider.bar_height      = 1;

        /* progressbar */
        ctx.style.progress.normal = nk_style_item_color(nk_rgb(231,231,231));
        ctx.style.progress.hover = nk_style_item_color(nk_rgb(231,231,231));
        ctx.style.progress.active = nk_style_item_color(nk_rgb(231,231,231));
        ctx.style.progress.cursor_normal = nk_style_item_color(nk_rgb(63,242,93));
        ctx.style.progress.cursor_hover = nk_style_item_color(nk_rgb(63,242,93));
        ctx.style.progress.cursor_active = nk_style_item_color(nk_rgb(63,242,93));
        ctx.style.progress.border_color = nk_rgb(114,116,115);
        ctx.style.progress.padding = nk_vec2(0,0);
        ctx.style.progress.border = 2;
        ctx.style.progress.rounding = 1;

        /* combo */
        ctx.style.combo.normal = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.combo.hover = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.combo.active = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.combo.border_color = nk_rgb(95,95,95);
        ctx.style.combo.label_normal = nk_rgb(95,95,95);
        ctx.style.combo.label_hover = nk_rgb(95,95,95);
        ctx.style.combo.label_active = nk_rgb(95,95,95);
        ctx.style.combo.border = 1;
        ctx.style.combo.rounding = 1;

        /* combo button */
        ctx.style.combo.button.normal = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.combo.button.hover = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.combo.button.active = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.combo.button.text_background = nk_rgb(216,216,216);
        ctx.style.combo.button.text_normal = nk_rgb(95,95,95);
        ctx.style.combo.button.text_hover = nk_rgb(95,95,95);
        ctx.style.combo.button.text_active = nk_rgb(95,95,95);

        /* property */
        ctx.style.property.normal = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.property.hover = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.property.active = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.property.border_color = nk_rgb(81,81,81);
        ctx.style.property.label_normal = nk_rgb(95,95,95);
        ctx.style.property.label_hover = nk_rgb(95,95,95);
        ctx.style.property.label_active = nk_rgb(95,95,95);
        ctx.style.property.sym_left = NK_SYMBOL_TRIANGLE_LEFT;
        ctx.style.property.sym_right = NK_SYMBOL_TRIANGLE_RIGHT;
        ctx.style.property.rounding = 10;
        ctx.style.property.border = 1;

        /* edit */
        ctx.style.edit.normal = nk_style_item_color(nk_rgb(240,240,240));
        ctx.style.edit.hover = nk_style_item_color(nk_rgb(240,240,240));
        ctx.style.edit.active = nk_style_item_color(nk_rgb(240,240,240));
        ctx.style.edit.border_color = nk_rgb(62,62,62);
        ctx.style.edit.cursor_normal = nk_rgb(99,202,255);
        ctx.style.edit.cursor_hover = nk_rgb(99,202,255);
        ctx.style.edit.cursor_text_normal = nk_rgb(95,95,95);
        ctx.style.edit.cursor_text_hover = nk_rgb(95,95,95);
        ctx.style.edit.text_normal = nk_rgb(95,95,95);
        ctx.style.edit.text_hover = nk_rgb(95,95,95);
        ctx.style.edit.text_active = nk_rgb(95,95,95);
        ctx.style.edit.selected_normal = nk_rgb(99,202,255);
        ctx.style.edit.selected_hover = nk_rgb(99,202,255);
        ctx.style.edit.selected_text_normal = nk_rgb(95,95,95);
        ctx.style.edit.selected_text_hover = nk_rgb(95,95,95);
        ctx.style.edit.border = 1;
        ctx.style.edit.rounding = 2;

        /* property buttons */
        ctx.style.property.dec_button.normal = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.property.dec_button.hover = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.property.dec_button.active = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.property.dec_button.text_background = nk_rgba(0,0,0,0);
        ctx.style.property.dec_button.text_normal = nk_rgb(95,95,95);
        ctx.style.property.dec_button.text_hover = nk_rgb(95,95,95);
        ctx.style.property.dec_button.text_active = nk_rgb(95,95,95);
        ctx.style.property.inc_button = ctx.style.property.dec_button;

        /* property edit */
        ctx.style.property.edit.normal = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.property.edit.hover = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.property.edit.active = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.property.edit.border_color = nk_rgba(0,0,0,0);
        ctx.style.property.edit.cursor_normal = nk_rgb(95,95,95);
        ctx.style.property.edit.cursor_hover = nk_rgb(95,95,95);
        ctx.style.property.edit.cursor_text_normal = nk_rgb(216,216,216);
        ctx.style.property.edit.cursor_text_hover = nk_rgb(216,216,216);
        ctx.style.property.edit.text_normal = nk_rgb(95,95,95);
        ctx.style.property.edit.text_hover = nk_rgb(95,95,95);
        ctx.style.property.edit.text_active = nk_rgb(95,95,95);
        ctx.style.property.edit.selected_normal = nk_rgb(95,95,95);
        ctx.style.property.edit.selected_hover = nk_rgb(95,95,95);
        ctx.style.property.edit.selected_text_normal = nk_rgb(216,216,216);
        ctx.style.property.edit.selected_text_hover = nk_rgb(216,216,216);

        /* chart */
        ctx.style.chart.background = nk_style_item_color(nk_rgb(216,216,216));
        ctx.style.chart.border_color = nk_rgb(81,81,81);
        ctx.style.chart.color = nk_rgb(95,95,95);
        ctx.style.chart.selected_color = nk_rgb(255,0,0);
        ctx.style.chart.border = 1;
    }

    while (!glfwWindowShouldClose(win))
    {
        /* High DPI displays */
        struct nk_vec2 scale;
        glfwGetWindowSize(win, &width, &height);
        glfwGetFramebufferSize(win, &display_width, &display_height);
        scale.x = (float)display_width/(float)width;
        scale.y = (float)display_height/(float)height;

        /* Input */
        {double x, y;
        nk_input_begin(&ctx);
        glfwPollEvents();
        nk_input_key(&ctx, NK_KEY_DEL, glfwGetKey(win, GLFW_KEY_DELETE) == GLFW_PRESS);
        nk_input_key(&ctx, NK_KEY_ENTER, glfwGetKey(win, GLFW_KEY_ENTER) == GLFW_PRESS);
        nk_input_key(&ctx, NK_KEY_TAB, glfwGetKey(win, GLFW_KEY_TAB) == GLFW_PRESS);
        nk_input_key(&ctx, NK_KEY_BACKSPACE, glfwGetKey(win, GLFW_KEY_BACKSPACE) == GLFW_PRESS);
        nk_input_key(&ctx, NK_KEY_LEFT, glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS);
        nk_input_key(&ctx, NK_KEY_RIGHT, glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS);
        nk_input_key(&ctx, NK_KEY_UP, glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS);
        nk_input_key(&ctx, NK_KEY_DOWN, glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS);
        if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
            glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
            nk_input_key(&ctx, NK_KEY_COPY, glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS);
            nk_input_key(&ctx, NK_KEY_PASTE, glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS);
            nk_input_key(&ctx, NK_KEY_CUT, glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS);
            nk_input_key(&ctx, NK_KEY_CUT, glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS);
            nk_input_key(&ctx, NK_KEY_SHIFT, 1);
        } else {
            nk_input_key(&ctx, NK_KEY_COPY, 0);
            nk_input_key(&ctx, NK_KEY_PASTE, 0);
            nk_input_key(&ctx, NK_KEY_CUT, 0);
            nk_input_key(&ctx, NK_KEY_SHIFT, 0);
        }
        glfwGetCursorPos(win, &x, &y);
        nk_input_motion(&ctx, (int)x, (int)y);
        nk_input_button(&ctx, NK_BUTTON_LEFT, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
        nk_input_button(&ctx, NK_BUTTON_MIDDLE, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
        nk_input_button(&ctx, NK_BUTTON_RIGHT, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
        nk_input_end(&ctx);}

        /* GUI */
        {struct nk_panel layout, tab;
        if (nk_begin(&ctx, "Demo", nk_rect(50, 50, 300, 400),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_TITLE))
        {
            int i;
            float id;
            static int slider = 10;
            static int field_len;
            static nk_size prog_value = 60;
            static int current_weapon = 0;
            static char field_buffer[64];
            static float pos;
            static const char *weapons[] = {"Fist","Pistol","Shotgun","Plasma","BFG"};
            const float step = (2*3.141592654f) / 32;

            nk_layout_row_static(&ctx, 30, 120, 1);
            if (nk_button_label(&ctx, "button"))
                fprintf(stdout, "button pressed\n");

            nk_layout_row_dynamic(&ctx, 20, 1);
            nk_label(&ctx, "Label", NK_TEXT_LEFT);
            nk_layout_row_dynamic(&ctx, 30, 2);
            nk_check_label(&ctx, "inactive", 0);
            nk_check_label(&ctx, "active", 1);
            nk_option_label(&ctx, "active", 1);
            nk_option_label(&ctx, "inactive", 0);

            nk_layout_row_dynamic(&ctx, 30, 1);
            nk_slider_int(&ctx, 0, &slider, 16, 1);
            nk_layout_row_dynamic(&ctx, 20, 1);
            nk_progress(&ctx, &prog_value, 100, NK_MODIFIABLE);

            nk_layout_row_dynamic(&ctx, 25, 1);
            nk_edit_string(&ctx, NK_EDIT_FIELD, field_buffer, &field_len, 64, nk_filter_default);
            nk_property_float(&ctx, "#X:", -1024.0f, &pos, 1024.0f, 1, 1);
            current_weapon = nk_combo(&ctx, weapons, LEN(weapons), current_weapon, 25, nk_vec2(nk_widget_width(&ctx),200));

            nk_layout_row_dynamic(&ctx, 100, 1);
            if (nk_chart_begin_colored(&ctx, NK_CHART_LINES, nk_rgb(255,0,0), nk_rgb(150,0,0), 32, 0.0f, 1.0f)) {
                nk_chart_add_slot_colored(&ctx, NK_CHART_LINES, nk_rgb(0,0,255), nk_rgb(0,0,150),32, -1.0f, 1.0f);
                nk_chart_add_slot_colored(&ctx, NK_CHART_LINES, nk_rgb(0,255,0), nk_rgb(0,150,0), 32, -1.0f, 1.0f);
                for (id = 0, i = 0; i < 32; ++i) {
                    nk_chart_push_slot(&ctx, (float)fabs(sin(id)), 0);
                    nk_chart_push_slot(&ctx, (float)cos(id), 1);
                    nk_chart_push_slot(&ctx, (float)sin(id), 2);
                    id += step;
                }
            }
            nk_chart_end(&ctx);

            nk_layout_row_dynamic(&ctx, 250, 1);
            if (nk_group_begin(&ctx, "Standard", NK_WINDOW_BORDER|NK_WINDOW_BORDER))
            {
                if (nk_tree_push(&ctx, NK_TREE_NODE, "Window", NK_MAXIMIZED)) {
                    static int selected[8];
                    if (nk_tree_push(&ctx, NK_TREE_NODE, "Next", NK_MAXIMIZED)) {
                        nk_layout_row_dynamic(&ctx, 20, 1);
                        for (i = 0; i < 4; ++i)
                            nk_selectable_label(&ctx, (selected[i]) ? "Selected": "Unselected", NK_TEXT_LEFT, &selected[i]);
                        nk_tree_pop(&ctx);
                    }
                    if (nk_tree_push(&ctx, NK_TREE_NODE, "Previous", NK_MAXIMIZED)) {
                        nk_layout_row_dynamic(&ctx, 20, 1);
                        for (i = 4; i < 8; ++i)
                            nk_selectable_label(&ctx, (selected[i]) ? "Selected": "Unselected", NK_TEXT_LEFT, &selected[i]);
                        nk_tree_pop(&ctx);
                    }
                    nk_tree_pop(&ctx);
                }
                nk_group_end(&ctx);
            }
        }
        nk_end(&ctx);}

        /* Draw */
        glViewport(0, 0, display_width, display_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5882, 0.6666, 0.6666, 1.0f);
        device_draw(&device, &ctx, width, height, scale, NK_ANTI_ALIASING_ON);
        glfwSwapBuffers(win);
    }
    glDeleteTextures(1,(const GLuint*)&media.skin);
    nk_font_atlas_clear(&atlas);
    nk_free(&ctx);
    device_shutdown(&device);
    glfwTerminate();
    return 0;
}