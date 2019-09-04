#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  frame_indicies ;
typedef  int /*<<< orphan*/  frame_coords ;
struct TYPE_5__ {int thermal_sock; int model_sock; int live100_sock; int uilayout_sock; int livecalibration_sock; int live20_sock; int livempc_sock; int plus_sock; int map_data_sock; int ipc_fd; int fb; int vg; scalar_t__ font_courbd; scalar_t__ font_sans_regular; scalar_t__ font_sans_semibold; scalar_t__ font_sans_bold; scalar_t__ img_wheel; scalar_t__ img_turn; scalar_t__ img_face; scalar_t__ img_map; int frame_program; int line_program; int passive; int model_changed; int livempc_or_live20_changed; int /*<<< orphan*/ ** priv_hnds_front; int /*<<< orphan*/ ** khr_front; int /*<<< orphan*/ ** priv_hnds; int /*<<< orphan*/ ** khr; void* rear_frame_mat; void* front_frame_mat; int /*<<< orphan*/ * frame_ibo; void* frame_texcoord_loc; void* frame_pos_loc; int /*<<< orphan*/ * frame_vbo; int /*<<< orphan*/ * frame_vao; int /*<<< orphan*/  fb_h; int /*<<< orphan*/  fb_w; void* line_transform_loc; void* line_color_loc; void* line_pos_loc; void* frame_transform_loc; void* frame_texture_loc; int /*<<< orphan*/  surface; int /*<<< orphan*/  display; void* map_data_sock_raw; void* plus_sock_raw; void* livempc_sock_raw; void* live20_sock_raw; void* livecalibration_sock_raw; void* uilayout_sock_raw; void* live100_sock_raw; void* model_sock_raw; void* thermal_sock_raw; int /*<<< orphan*/  bg_cond; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ UIState ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int NVG_ANTIALIAS ; 
 int NVG_DEBUG ; 
 int NVG_STENCIL_STROKES ; 
 int UI_BUF_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  device_transform ; 
 int /*<<< orphan*/  frame_fragment_shader ; 
 int /*<<< orphan*/  frame_transform ; 
 int /*<<< orphan*/  frame_vertex_shader ; 
 int framebuffer_init (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  full_to_wide_frame_transform ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindVertexArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (void*) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenVertexArrays (int,int /*<<< orphan*/ *) ; 
 void* glGetAttribLocation (int,char*) ; 
 scalar_t__ glGetError () ; 
 void* glGetUniformLocation (int,char*) ; 
 int /*<<< orphan*/  glVertexAttribPointer (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void const*) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_fragment_shader ; 
 int /*<<< orphan*/  line_vertex_shader ; 
 void* load_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* matmul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* nvgCreateFont (int,char*,char*) ; 
 int nvgCreateGLES3 (int) ; 
 void* nvgCreateImage (int,char*,int) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_db_value (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_awake (TYPE_1__*,int) ; 
 void* zsock_new_sub (char*,char*) ; 
 void* zsock_resolve (int) ; 

__attribute__((used)) static void ui_init(UIState *s) {
  memset(s, 0, sizeof(UIState));

  pthread_mutex_init(&s->lock, NULL);
  pthread_cond_init(&s->bg_cond, NULL);

  // init connections

  s->thermal_sock = zsock_new_sub(">tcp://127.0.0.1:8005", "");
  assert(s->thermal_sock);
  s->thermal_sock_raw = zsock_resolve(s->thermal_sock);

  s->model_sock = zsock_new_sub(">tcp://127.0.0.1:8009", "");
  assert(s->model_sock);
  s->model_sock_raw = zsock_resolve(s->model_sock);

  s->live100_sock = zsock_new_sub(">tcp://127.0.0.1:8007", "");
  assert(s->live100_sock);
  s->live100_sock_raw = zsock_resolve(s->live100_sock);

  s->uilayout_sock = zsock_new_sub(">tcp://127.0.0.1:8060", "");
  assert(s->uilayout_sock);
  s->uilayout_sock_raw = zsock_resolve(s->uilayout_sock);

  s->livecalibration_sock = zsock_new_sub(">tcp://127.0.0.1:8019", "");
  assert(s->livecalibration_sock);
  s->livecalibration_sock_raw = zsock_resolve(s->livecalibration_sock);

  s->live20_sock = zsock_new_sub(">tcp://127.0.0.1:8012", "");
  assert(s->live20_sock);
  s->live20_sock_raw = zsock_resolve(s->live20_sock);

  s->livempc_sock = zsock_new_sub(">tcp://127.0.0.1:8035", "");
  assert(s->livempc_sock);
  s->livempc_sock_raw = zsock_resolve(s->livempc_sock);

  s->plus_sock = zsock_new_sub(">tcp://127.0.0.1:8037", "");
  assert(s->plus_sock);
  s->plus_sock_raw = zsock_resolve(s->plus_sock);

  s->map_data_sock = zsock_new_sub(">tcp://127.0.0.1:8065", "");
  assert(s->map_data_sock);
  s->map_data_sock_raw = zsock_resolve(s->map_data_sock);

  s->ipc_fd = -1;

  // init display
  s->fb = framebuffer_init("ui", 0x00010000, true,
                           &s->display, &s->surface, &s->fb_w, &s->fb_h);
  assert(s->fb);

  set_awake(s, true);

  // init drawing
  s->vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
  assert(s->vg);

  s->font_courbd = nvgCreateFont(s->vg, "courbd", "../assets/courbd.ttf");
  assert(s->font_courbd >= 0);
  s->font_sans_regular = nvgCreateFont(s->vg, "sans-regular", "../assets/OpenSans-Regular.ttf");
  assert(s->font_sans_regular >= 0);
  s->font_sans_semibold = nvgCreateFont(s->vg, "sans-semibold", "../assets/OpenSans-SemiBold.ttf");
  assert(s->font_sans_semibold >= 0);
  s->font_sans_bold = nvgCreateFont(s->vg, "sans-bold", "../assets/OpenSans-Bold.ttf");
  assert(s->font_sans_bold >= 0);

  assert(s->img_wheel >= 0);
  s->img_wheel = nvgCreateImage(s->vg, "../assets/img_chffr_wheel.png", 1);

  assert(s->img_turn >= 0);
  s->img_turn = nvgCreateImage(s->vg, "../assets/img_trafficSign_turn.png", 1);

  assert(s->img_face >= 0);
  s->img_face = nvgCreateImage(s->vg, "../assets/img_driver_face.png", 1);

  assert(s->img_map >= 0);
  s->img_map = nvgCreateImage(s->vg, "../assets/img_map.png", 1);

  // init gl
  s->frame_program = load_program(frame_vertex_shader, frame_fragment_shader);
  assert(s->frame_program);

  s->frame_pos_loc = glGetAttribLocation(s->frame_program, "aPosition");
  s->frame_texcoord_loc = glGetAttribLocation(s->frame_program, "aTexCoord");

  s->frame_texture_loc = glGetUniformLocation(s->frame_program, "uTexture");
  s->frame_transform_loc = glGetUniformLocation(s->frame_program, "uTransform");

  s->line_program = load_program(line_vertex_shader, line_fragment_shader);
  assert(s->line_program);

  s->line_pos_loc = glGetAttribLocation(s->line_program, "aPosition");
  s->line_color_loc = glGetAttribLocation(s->line_program, "aColor");
  s->line_transform_loc = glGetUniformLocation(s->line_program, "uTransform");

  glViewport(0, 0, s->fb_w, s->fb_h);

  glDisable(GL_DEPTH_TEST);

  assert(glGetError() == GL_NO_ERROR);

  {
    char *value;
    const int result = read_db_value(NULL, "Passive", &value, NULL);
    if (result == 0) {
      s->passive = value[0] == '1';
      free(value);
    }
  }
  for(int i = 0; i < 2; i++) {
    float x1, x2, y1, y2;
    if (i == 1) {
      // flip horizontally so it looks like a mirror
      x1 = 0.0;
      x2 = 1.0;
      y1 = 1.0;
      y2 = 0.0;
    } else {
      x1 = 1.0;
      x2 = 0.0;
      y1 = 1.0;
      y2 = 0.0;
    }
    const uint8_t frame_indicies[] = {0, 1, 2, 0, 2, 3};
    const float frame_coords[4][4] = {
      {-1.0, -1.0, x2, y1}, //bl
      {-1.0,  1.0, x2, y2}, //tl
      { 1.0,  1.0, x1, y2}, //tr
      { 1.0, -1.0, x1, y1}, //br
    };

    glGenVertexArrays(1,&s->frame_vao[i]);
    glBindVertexArray(s->frame_vao[i]);
    glGenBuffers(1, &s->frame_vbo[i]);
    glBindBuffer(GL_ARRAY_BUFFER, s->frame_vbo[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(frame_coords), frame_coords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(s->frame_pos_loc);
    glVertexAttribPointer(s->frame_pos_loc, 2, GL_FLOAT, GL_FALSE,
                          sizeof(frame_coords[0]), (const void *)0);
    glEnableVertexAttribArray(s->frame_texcoord_loc);
    glVertexAttribPointer(s->frame_texcoord_loc, 2, GL_FLOAT, GL_FALSE,
                          sizeof(frame_coords[0]), (const void *)(sizeof(float) * 2));
    glGenBuffers(1, &s->frame_ibo[i]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s->frame_ibo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(frame_indicies), frame_indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
  }

  s->model_changed = false;
  s->livempc_or_live20_changed = false;

  s->front_frame_mat = matmul(device_transform, full_to_wide_frame_transform);
  s->rear_frame_mat = matmul(device_transform, frame_transform);

  for(int i = 0;i < UI_BUF_COUNT; i++) {
    s->khr[i] = NULL;
    s->priv_hnds[i] = NULL;
    s->khr_front[i] = NULL;
    s->priv_hnds_front[i] = NULL;
  }
}