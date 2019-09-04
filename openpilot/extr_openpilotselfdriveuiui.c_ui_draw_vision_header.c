#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ui_viz_rx; int ui_viz_rw; } ;
struct TYPE_8__ {int /*<<< orphan*/  vg; TYPE_2__ scene; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;
typedef  int /*<<< orphan*/  NVGpaint ;

/* Variables and functions */
 double box_y ; 
 double header_h ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgLinearGradient (int /*<<< orphan*/ ,int,double,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgRGBAf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  nvgRect (int /*<<< orphan*/ ,int,double,int,double) ; 
 int /*<<< orphan*/  ui_draw_vision_event (TYPE_1__*) ; 
 int /*<<< orphan*/  ui_draw_vision_maxspeed (TYPE_1__*) ; 
 int /*<<< orphan*/  ui_draw_vision_speed (TYPE_1__*) ; 
 int /*<<< orphan*/  ui_draw_vision_speedlimit (TYPE_1__*) ; 

__attribute__((used)) static void ui_draw_vision_header(UIState *s) {
  const UIScene *scene = &s->scene;
  int ui_viz_rx = scene->ui_viz_rx;
  int ui_viz_rw = scene->ui_viz_rw;

  nvgBeginPath(s->vg);
  NVGpaint gradient = nvgLinearGradient(s->vg, ui_viz_rx,
                        (box_y+(header_h-(header_h/2.5))),
                        ui_viz_rx, box_y+header_h,
                        nvgRGBAf(0,0,0,0.45), nvgRGBAf(0,0,0,0));
  nvgFillPaint(s->vg, gradient);
  nvgRect(s->vg, ui_viz_rx, box_y, ui_viz_rw, header_h);
  nvgFill(s->vg);

  ui_draw_vision_maxspeed(s);
  ui_draw_vision_speedlimit(s);
  ui_draw_vision_speed(s);
  ui_draw_vision_event(s);
}