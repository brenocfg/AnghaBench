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
struct TYPE_5__ {int ui_viz_rx; int ui_viz_rw; int engageable; scalar_t__ engaged; scalar_t__ decel_for_turn; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  vg; int /*<<< orphan*/  img_wheel; int /*<<< orphan*/  img_turn; scalar_t__ limit_set_speed; TYPE_2__ scene; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;
typedef  int /*<<< orphan*/  NVGpaint ;

/* Variables and functions */
 scalar_t__ STATUS_ENGAGED ; 
 scalar_t__ STATUS_WARNING ; 
 int bdr_s ; 
 int box_y ; 
 int header_h ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgCircle (int /*<<< orphan*/ ,int const,int const,int const) ; 
 int /*<<< orphan*/  nvgFill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgImagePattern (int /*<<< orphan*/ ,int const,int const,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  nvgRGBA (int,int,int,int) ; 
 int /*<<< orphan*/  nvgRect (int /*<<< orphan*/ ,int const,int const,int const,int const) ; 

__attribute__((used)) static void ui_draw_vision_event(UIState *s) {
  const UIScene *scene = &s->scene;
  const int ui_viz_rx = scene->ui_viz_rx;
  const int ui_viz_rw = scene->ui_viz_rw;
  const int viz_event_w = 220;
  const int viz_event_x = ((ui_viz_rx + ui_viz_rw) - (viz_event_w + (bdr_s*2)));
  const int viz_event_y = (box_y + (bdr_s*1.5));
  const int viz_event_h = (header_h - (bdr_s*1.5));
  if (s->scene.decel_for_turn && s->scene.engaged && s->limit_set_speed) {
    // draw winding road sign
    const int img_turn_size = 160*1.5;
    const int img_turn_x = viz_event_x-(img_turn_size/4);
    const int img_turn_y = viz_event_y+bdr_s-25;
    float img_turn_alpha = 1.0f;
    nvgBeginPath(s->vg);
    NVGpaint imgPaint = nvgImagePattern(s->vg, img_turn_x, img_turn_y,
      img_turn_size, img_turn_size, 0, s->img_turn, img_turn_alpha);
    nvgRect(s->vg, img_turn_x, img_turn_y, img_turn_size, img_turn_size);
    nvgFillPaint(s->vg, imgPaint);
    nvgFill(s->vg);
  } else {
    // draw steering wheel
    const int bg_wheel_size = 96;
    const int bg_wheel_x = viz_event_x + (viz_event_w-bg_wheel_size);
    const int bg_wheel_y = viz_event_y + (bg_wheel_size/2);
    const int img_wheel_size = bg_wheel_size*1.5;
    const int img_wheel_x = bg_wheel_x-(img_wheel_size/2);
    const int img_wheel_y = bg_wheel_y-25;
    float img_wheel_alpha = 0.1f;
    bool is_engaged = (s->status == STATUS_ENGAGED);
    bool is_warning = (s->status == STATUS_WARNING);
    bool is_engageable = scene->engageable;
    if (is_engaged || is_warning || is_engageable) {
      nvgBeginPath(s->vg);
      nvgCircle(s->vg, bg_wheel_x, (bg_wheel_y + (bdr_s*1.5)), bg_wheel_size);
      if (is_engaged) {
        nvgFillColor(s->vg, nvgRGBA(23, 134, 68, 255));
      } else if (is_warning) {
        nvgFillColor(s->vg, nvgRGBA(218, 111, 37, 255));
      } else if (is_engageable) {
        nvgFillColor(s->vg, nvgRGBA(23, 51, 73, 255));
      }
      nvgFill(s->vg);
      img_wheel_alpha = 1.0f;
    }
    nvgBeginPath(s->vg);
    NVGpaint imgPaint = nvgImagePattern(s->vg, img_wheel_x, img_wheel_y,
      img_wheel_size, img_wheel_size, 0, s->img_wheel, img_wheel_alpha);
    nvgRect(s->vg, img_wheel_x, img_wheel_y, img_wheel_size, img_wheel_size);
    nvgFillPaint(s->vg, imgPaint);
    nvgFill(s->vg);
  }
}