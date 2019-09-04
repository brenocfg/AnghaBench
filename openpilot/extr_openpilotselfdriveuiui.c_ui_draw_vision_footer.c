#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ui_viz_rx; int ui_viz_rw; } ;
struct TYPE_6__ {int /*<<< orphan*/  vg; TYPE_2__ scene; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;

/* Variables and functions */
 int /*<<< orphan*/  footer_h ; 
 int /*<<< orphan*/  footer_y ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgRect (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_draw_vision_face (TYPE_1__*) ; 
 int /*<<< orphan*/  ui_draw_vision_map (TYPE_1__*) ; 

__attribute__((used)) static void ui_draw_vision_footer(UIState *s) {
  const UIScene *scene = &s->scene;
  int ui_viz_rx = scene->ui_viz_rx;
  int ui_viz_rw = scene->ui_viz_rw;

  nvgBeginPath(s->vg);
  nvgRect(s->vg, ui_viz_rx, footer_y, ui_viz_rw, footer_h);

  ui_draw_vision_face(s);
  ui_draw_vision_map(s);
}