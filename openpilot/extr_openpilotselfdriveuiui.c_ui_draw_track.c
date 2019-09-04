#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int cnt; TYPE_2__* v; } ;
typedef  TYPE_3__ track_vertices_data ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
struct TYPE_12__ {float* mpc_x; float* mpc_y; int lead_d_rel; TYPE_1__ model; } ;
struct TYPE_11__ {float rgb_width; float rgb_height; size_t status; int /*<<< orphan*/  vg; TYPE_5__ scene; } ;
typedef  TYPE_4__ UIState ;
typedef  TYPE_5__ UIScene ;
struct TYPE_9__ {scalar_t__ x; scalar_t__ y; } ;
typedef  int /*<<< orphan*/  PathData ;
typedef  int /*<<< orphan*/  NVGpaint ;

/* Variables and functions */
 int** bg_colors ; 
 int min (float,int) ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgClosePath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgLineTo (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nvgLinearGradient (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgMoveTo (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nvgRGBA (int const,int const,int const,int) ; 
 int /*<<< orphan*/  nvgRestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgSave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgScale (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  nvgTranslate (int /*<<< orphan*/ ,float,float) ; 
 double vwp_h ; 
 int /*<<< orphan*/  vwp_w ; 

__attribute__((used)) static void ui_draw_track(UIState *s, bool is_mpc, track_vertices_data *pvd) {
const UIScene *scene = &s->scene;
  const PathData path = scene->model.path;
  const float *mpc_x_coords = &scene->mpc_x[0];
  const float *mpc_y_coords = &scene->mpc_y[0];

  nvgSave(s->vg);
  nvgTranslate(s->vg, 240.0f, 0.0); // rgb-box space
  nvgTranslate(s->vg, -1440.0f / 2, -1080.0f / 2); // zoom 2x
  nvgScale(s->vg, 2.0, 2.0);
  nvgScale(s->vg, 1440.0f / s->rgb_width, 1080.0f / s->rgb_height);
  nvgBeginPath(s->vg);

  bool started = false;
  float off = is_mpc?0.3:0.5;
  float lead_d = scene->lead_d_rel*2.;
  float path_height = is_mpc?(lead_d>5.)?min(lead_d, 25.)-min(lead_d*0.35, 10.):20.
                            :(lead_d>0.)?min(lead_d, 50.)-min(lead_d*0.35, 10.):49.;
  int vi = 0;
  for(int i = 0;i < pvd->cnt;i++) {
    if (pvd->v[i].x < 0 || pvd->v[i].y < 0) {
      continue;
    }

    if (!started) {
      nvgMoveTo(s->vg, pvd->v[i].x, pvd->v[i].y);
      started = true;
    } else {
      nvgLineTo(s->vg, pvd->v[i].x, pvd->v[i].y);
    }
  }

  nvgClosePath(s->vg);

  NVGpaint track_bg;
  if (is_mpc) {
    // Draw colored MPC track
    const uint8_t *clr = bg_colors[s->status];
    track_bg = nvgLinearGradient(s->vg, vwp_w, vwp_h, vwp_w, vwp_h*.4,
      nvgRGBA(clr[0], clr[1], clr[2], 255), nvgRGBA(clr[0], clr[1], clr[2], 255/2));
  } else {
    // Draw white vision track
    track_bg = nvgLinearGradient(s->vg, vwp_w, vwp_h, vwp_w, vwp_h*.4,
      nvgRGBA(255, 255, 255, 255), nvgRGBA(255, 255, 255, 0));
  }

  nvgFillPaint(s->vg, track_bg);
  nvgFill(s->vg);
  nvgRestore(s->vg);
}