#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cnt; TYPE_1__* v; } ;
typedef  TYPE_2__ model_path_vertices_data ;
struct TYPE_8__ {float rgb_width; float rgb_height; int /*<<< orphan*/  vg; int /*<<< orphan*/  scene; } ;
typedef  TYPE_3__ UIState ;
typedef  int /*<<< orphan*/  UIScene ;
struct TYPE_6__ {scalar_t__ x; int y; } ;
typedef  int /*<<< orphan*/  NVGcolor ;

/* Variables and functions */
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgClosePath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgLineTo (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  nvgMoveTo (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  nvgRestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgSave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgScale (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  nvgTranslate (int /*<<< orphan*/ ,float,float) ; 

__attribute__((used)) static void ui_draw_lane_line(UIState *s, const model_path_vertices_data *pvd, NVGcolor color) {
  const UIScene *scene = &s->scene;

  nvgSave(s->vg);
  nvgTranslate(s->vg, 240.0f, 0.0); // rgb-box space
  nvgTranslate(s->vg, -1440.0f / 2, -1080.0f / 2); // zoom 2x
  nvgScale(s->vg, 2.0, 2.0);
  nvgScale(s->vg, 1440.0f / s->rgb_width, 1080.0f / s->rgb_height);
  nvgBeginPath(s->vg);

  bool started = false;
  for (int i=0; i<pvd->cnt; i++) {
    if (pvd->v[i].x < 0 || pvd->v[i].y < 0.) {
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
  nvgFillColor(s->vg, color);
  nvgFill(s->vg);
  nvgRestore(s->vg);
}