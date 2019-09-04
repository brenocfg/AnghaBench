#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ui_viz_rx; int ui_viz_rw; int ui_viz_ro; scalar_t__ alert_size; int /*<<< orphan*/  alert_text2; int /*<<< orphan*/  alert_text1; int /*<<< orphan*/  fullview; int /*<<< orphan*/  frontview; } ;
struct TYPE_9__ {int const fb_h; int fb_w; int /*<<< orphan*/  vg; TYPE_2__ scene; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;

/* Variables and functions */
 scalar_t__ ALERTSIZE_NONE ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int GL_STENCIL_BUFFER_BIT ; 
 int const box_h ; 
 scalar_t__ box_y ; 
 int /*<<< orphan*/  draw_frame (TYPE_1__*) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (double,double,double,double) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glScissor (int,scalar_t__,int,int const) ; 
 int /*<<< orphan*/  glViewport (int,scalar_t__,int,int const) ; 
 int /*<<< orphan*/  nvgBeginFrame (int /*<<< orphan*/ ,int,int const,float) ; 
 int /*<<< orphan*/  nvgEndFrame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgRestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgSave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgScale (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  nvgScissor (int /*<<< orphan*/ ,int,scalar_t__,int,int const) ; 
 int /*<<< orphan*/  nvgTranslate (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  ui_draw_vision_alert (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_draw_vision_footer (TYPE_1__*) ; 
 int /*<<< orphan*/  ui_draw_vision_header (TYPE_1__*) ; 
 int /*<<< orphan*/  ui_draw_world (TYPE_1__*) ; 
 int viz_w ; 

__attribute__((used)) static void ui_draw_vision(UIState *s) {
  const UIScene *scene = &s->scene;
  int ui_viz_rx = scene->ui_viz_rx;
  int ui_viz_rw = scene->ui_viz_rw;
  int ui_viz_ro = scene->ui_viz_ro;

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  // Draw video frames
  glEnable(GL_SCISSOR_TEST);
  glViewport(ui_viz_rx+ui_viz_ro, s->fb_h-(box_y+box_h), viz_w, box_h);
  glScissor(ui_viz_rx, s->fb_h-(box_y+box_h), ui_viz_rw, box_h);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  draw_frame(s);
  glViewport(0, 0, s->fb_w, s->fb_h);
  glDisable(GL_SCISSOR_TEST);

  glClear(GL_STENCIL_BUFFER_BIT);
 
  nvgBeginFrame(s->vg, s->fb_w, s->fb_h, 1.0f);
  nvgSave(s->vg);

  // Draw augmented elements
  const int inner_height = viz_w*9/16;
  nvgScissor(s->vg, ui_viz_rx, box_y, ui_viz_rw, box_h);
  nvgTranslate(s->vg, ui_viz_rx+ui_viz_ro, box_y + (box_h-inner_height)/2.0);
  nvgScale(s->vg, (float)viz_w / s->fb_w, (float)inner_height / s->fb_h);
  if (!scene->frontview && !scene->fullview) {
    ui_draw_world(s);
  }

  nvgRestore(s->vg);

  // Set Speed, Current Speed, Status/Events
  ui_draw_vision_header(s);

  if (s->scene.alert_size != ALERTSIZE_NONE) {
    // Controls Alerts
    ui_draw_vision_alert(s, s->scene.alert_size, s->status,
                            s->scene.alert_text1, s->scene.alert_text2);
  } else {
    ui_draw_vision_footer(s);
  }


  nvgEndFrame(s->vg);
  glDisable(GL_BLEND);
}