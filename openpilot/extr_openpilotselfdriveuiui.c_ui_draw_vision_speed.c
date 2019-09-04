#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  speed_str ;
struct TYPE_5__ {int ui_viz_rx; int ui_viz_rw; float v_ego; } ;
struct TYPE_4__ {int /*<<< orphan*/  vg; scalar_t__ is_metric; TYPE_2__ scene; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;

/* Variables and functions */
 int NVG_ALIGN_BASELINE ; 
 int NVG_ALIGN_CENTER ; 
 int /*<<< orphan*/  box_y ; 
 int /*<<< orphan*/  header_h ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFontFace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvgFontSize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgRGBA (int,int,int,int) ; 
 int /*<<< orphan*/  nvgRect (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgText (int /*<<< orphan*/ ,int const,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgTextAlign (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void ui_draw_vision_speed(UIState *s) {
  const UIScene *scene = &s->scene;
  int ui_viz_rx = scene->ui_viz_rx;
  int ui_viz_rw = scene->ui_viz_rw;
  float speed = s->scene.v_ego;

  const int viz_speed_w = 280;
  const int viz_speed_x = ui_viz_rx+((ui_viz_rw/2)-(viz_speed_w/2));
  char speed_str[32];

  nvgBeginPath(s->vg);
  nvgRect(s->vg, viz_speed_x, box_y, viz_speed_w, header_h);
  nvgTextAlign(s->vg, NVG_ALIGN_CENTER | NVG_ALIGN_BASELINE);

  if (s->is_metric) {
    snprintf(speed_str, sizeof(speed_str), "%d", (int)(speed * 3.6 + 0.5));
  } else {
    snprintf(speed_str, sizeof(speed_str), "%d", (int)(speed * 2.2369363 + 0.5));
  }
  nvgFontFace(s->vg, "sans-bold");
  nvgFontSize(s->vg, 96*2.5);
  nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 255));
  nvgText(s->vg, viz_speed_x+viz_speed_w/2, 240, speed_str, NULL);

  nvgFontFace(s->vg, "sans-regular");
  nvgFontSize(s->vg, 36*2.5);
  nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 200));

  if (s->is_metric) {
    nvgText(s->vg, viz_speed_x+viz_speed_w/2, 320, "kph", NULL);
  } else {
    nvgText(s->vg, viz_speed_x+viz_speed_w/2, 320, "mph", NULL);
  }
}