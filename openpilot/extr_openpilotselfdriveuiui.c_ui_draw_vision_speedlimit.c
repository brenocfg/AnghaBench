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
typedef  int /*<<< orphan*/  speedlim_str ;
struct TYPE_5__ {int ui_viz_rx; int ui_viz_rw; float speedlimit; int speedlimit_valid; scalar_t__ v_ego; } ;
struct TYPE_4__ {int is_ego_over_limit; scalar_t__ speed_lim_off; int /*<<< orphan*/  vg; TYPE_2__ scene; scalar_t__ is_metric; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;

/* Variables and functions */
 int NVG_ALIGN_BASELINE ; 
 int NVG_ALIGN_CENTER ; 
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

__attribute__((used)) static void ui_draw_vision_speedlimit(UIState *s) {
  const UIScene *scene = &s->scene;
  int ui_viz_rx = scene->ui_viz_rx;
  int ui_viz_rw = scene->ui_viz_rw;

  char speedlim_str[32];
  float speedlimit = s->scene.speedlimit;
  int speedlim_calc = speedlimit * 2.2369363 + 0.5;
  if (s->is_metric) {
    speedlim_calc = speedlimit * 3.6 + 0.5;
  }

  bool is_speedlim_valid = s->scene.speedlimit_valid;
  float hysteresis_offset = 0.5;
  if (s->is_ego_over_limit) {
    hysteresis_offset = 0.0;
  }
  s->is_ego_over_limit = is_speedlim_valid && s->scene.v_ego > (speedlimit + s->speed_lim_off + hysteresis_offset);

  int viz_speedlim_w = 180;
  int viz_speedlim_h = 202;
  int viz_speedlim_x = (ui_viz_rx + (bdr_s*2));
  int viz_speedlim_y = (box_y + (bdr_s*1.5));
  if (!is_speedlim_valid) {
    viz_speedlim_w -= 5;
    viz_speedlim_h -= 10;
    viz_speedlim_x += 9;
    viz_speedlim_y += 5;
  }
  int viz_speedlim_bdr = is_speedlim_valid ? 30 : 15;

  // Draw Background
  nvgBeginPath(s->vg);
  nvgRoundedRect(s->vg, viz_speedlim_x, viz_speedlim_y, viz_speedlim_w, viz_speedlim_h, viz_speedlim_bdr);
  if (is_speedlim_valid && s->is_ego_over_limit) {
    nvgFillColor(s->vg, nvgRGBA(218, 111, 37, 180));
  } else if (is_speedlim_valid) {
    nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 255));
  } else {
    nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 100));
  }
  nvgFill(s->vg);

  // Draw Border
  if (is_speedlim_valid) {
    nvgStrokeWidth(s->vg, 10);
    nvgStroke(s->vg);
    nvgBeginPath(s->vg);
    nvgRoundedRect(s->vg, viz_speedlim_x, viz_speedlim_y, viz_speedlim_w, viz_speedlim_h, 20);
    if (s->is_ego_over_limit) {
      nvgStrokeColor(s->vg, nvgRGBA(218, 111, 37, 255));
    } else if (is_speedlim_valid) {
      nvgStrokeColor(s->vg, nvgRGBA(255, 255, 255, 255));
    }
  }

  // Draw "Speed Limit" Text
  nvgTextAlign(s->vg, NVG_ALIGN_CENTER | NVG_ALIGN_BASELINE);
  nvgFontFace(s->vg, "sans-semibold");
  nvgFontSize(s->vg, 50);
  nvgFillColor(s->vg, nvgRGBA(0, 0, 0, 255));
  if (is_speedlim_valid && s->is_ego_over_limit) {
    nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 255));
  }
  nvgText(s->vg, viz_speedlim_x+viz_speedlim_w/2 + (is_speedlim_valid ? 6 : 0), viz_speedlim_y + (is_speedlim_valid ? 50 : 45), "SPEED", NULL);
  nvgText(s->vg, viz_speedlim_x+viz_speedlim_w/2 + (is_speedlim_valid ? 6 : 0), viz_speedlim_y + (is_speedlim_valid ? 90 : 85), "LIMIT", NULL);

  // Draw Speed Text
  nvgFontFace(s->vg, "sans-bold");
  nvgFontSize(s->vg, 48*2.5);
  if (s->is_ego_over_limit) {
    nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 255));
  } else {
    nvgFillColor(s->vg, nvgRGBA(0, 0, 0, 255));
  }
  if (is_speedlim_valid) {
    snprintf(speedlim_str, sizeof(speedlim_str), "%d", speedlim_calc);
    nvgText(s->vg, viz_speedlim_x+viz_speedlim_w/2, viz_speedlim_y + (is_speedlim_valid ? 170 : 165), speedlim_str, NULL);
  } else {
    nvgFontFace(s->vg, "sans-semibold");
    nvgFontSize(s->vg, 42*2.5);
    nvgText(s->vg, viz_speedlim_x+viz_speedlim_w/2, viz_speedlim_y + (is_speedlim_valid ? 170 : 165), "N/A", NULL);
  }
}