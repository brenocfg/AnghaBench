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
typedef  int /*<<< orphan*/  maxspeed_str ;
struct TYPE_5__ {int ui_viz_rx; int ui_viz_rw; float v_cruise; float speedlimit; int speedlimit_valid; scalar_t__ engaged; } ;
struct TYPE_4__ {double speed_lim_off; int /*<<< orphan*/  vg; scalar_t__ is_ego_over_limit; TYPE_2__ scene; scalar_t__ is_metric; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;

/* Variables and functions */
 int NVG_ALIGN_BASELINE ; 
 int NVG_ALIGN_CENTER ; 
 float SET_SPEED_NA ; 
 int bdr_s ; 
 int box_y ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFontFace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvgFontSize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgRGBA (int,int,int,int) ; 
 int /*<<< orphan*/  nvgRoundedRect (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  nvgStroke (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgStrokeColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgStrokeWidth (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgText (int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgTextAlign (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void ui_draw_vision_maxspeed(UIState *s) {
  const UIScene *scene = &s->scene;
  int ui_viz_rx = scene->ui_viz_rx;
  int ui_viz_rw = scene->ui_viz_rw;

  char maxspeed_str[32];
  float maxspeed = s->scene.v_cruise;
  int maxspeed_calc = maxspeed * 0.6225 + 0.5;
  float speedlimit = s->scene.speedlimit;
  int speedlim_calc = speedlimit * 2.2369363 + 0.5;
  int speed_lim_off = s->speed_lim_off * 2.2369363 + 0.5;
  if (s->is_metric) {
    maxspeed_calc = maxspeed + 0.5;
    speedlim_calc = speedlimit * 3.6 + 0.5;
    speed_lim_off = s->speed_lim_off * 3.6 + 0.5;
  }

  bool is_cruise_set = (maxspeed != 0 && maxspeed != SET_SPEED_NA);
  bool is_speedlim_valid = s->scene.speedlimit_valid;
  bool is_set_over_limit = is_speedlim_valid && s->scene.engaged &&
                       is_cruise_set && maxspeed_calc > (speedlim_calc + speed_lim_off);

  int viz_maxspeed_w = 184;
  int viz_maxspeed_h = 202;
  int viz_maxspeed_x = (ui_viz_rx + (bdr_s*2));
  int viz_maxspeed_y = (box_y + (bdr_s*1.5));
  int viz_maxspeed_xo = 180;
  viz_maxspeed_w += viz_maxspeed_xo;
  viz_maxspeed_x += viz_maxspeed_w - (viz_maxspeed_xo * 2);

  // Draw Background
  nvgBeginPath(s->vg);
  nvgRoundedRect(s->vg, viz_maxspeed_x, viz_maxspeed_y, viz_maxspeed_w, viz_maxspeed_h, 30);
  if (is_set_over_limit) {
    nvgFillColor(s->vg, nvgRGBA(218, 111, 37, 180));
  } else {
    nvgFillColor(s->vg, nvgRGBA(0, 0, 0, 100));
  }
  nvgFill(s->vg);

  // Draw Border
  nvgBeginPath(s->vg);
  nvgRoundedRect(s->vg, viz_maxspeed_x, viz_maxspeed_y, viz_maxspeed_w, viz_maxspeed_h, 20);
  if (is_set_over_limit) {
    nvgStrokeColor(s->vg, nvgRGBA(218, 111, 37, 255));
  } else if (is_speedlim_valid && !s->is_ego_over_limit) {
    nvgStrokeColor(s->vg, nvgRGBA(255, 255, 255, 255));
  } else if (is_speedlim_valid && s->is_ego_over_limit) {
    nvgStrokeColor(s->vg, nvgRGBA(255, 255, 255, 20));
  } else {
    nvgStrokeColor(s->vg, nvgRGBA(255, 255, 255, 100));
  }
  nvgStrokeWidth(s->vg, 10);
  nvgStroke(s->vg);

  // Draw "MAX" Text
  nvgTextAlign(s->vg, NVG_ALIGN_CENTER | NVG_ALIGN_BASELINE);
  nvgFontFace(s->vg, "sans-regular");
  nvgFontSize(s->vg, 26*2.5);
  if (is_cruise_set) {
    nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 200));
  } else {
    nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 100));
  }
  nvgText(s->vg, viz_maxspeed_x+(viz_maxspeed_xo/2)+(viz_maxspeed_w/2), 148, "MAX", NULL);

  // Draw Speed Text
  nvgFontFace(s->vg, "sans-bold");
  nvgFontSize(s->vg, 48*2.5);
  if (is_cruise_set) {
    snprintf(maxspeed_str, sizeof(maxspeed_str), "%d", maxspeed_calc);
    nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 255));
    nvgText(s->vg, viz_maxspeed_x+(viz_maxspeed_xo/2)+(viz_maxspeed_w/2), 242, maxspeed_str, NULL);
  } else {
    nvgFontFace(s->vg, "sans-semibold");
    nvgFontSize(s->vg, 42*2.5);
    nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 100));
    nvgText(s->vg, viz_maxspeed_x+(viz_maxspeed_xo/2)+(viz_maxspeed_w/2), 242, "N/A", NULL);
  }

#ifdef DEBUG_TURN
  if (s->scene.decel_for_turn && s->scene.engaged){
    int v_curvature = s->scene.v_curvature * 2.2369363 + 0.5;
    snprintf(maxspeed_str, sizeof(maxspeed_str), "%d", v_curvature);
    nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 255));
    nvgFontSize(s->vg, 25*2.5);
    nvgText(s->vg, 200 + viz_maxspeed_x+(viz_maxspeed_xo/2)+(viz_maxspeed_w/2), 148, "TURN", NULL);
    nvgFontSize(s->vg, 50*2.5);
    nvgText(s->vg, 200 + viz_maxspeed_x+(viz_maxspeed_xo/2)+(viz_maxspeed_w/2), 242, maxspeed_str, NULL);
  }
#endif
}