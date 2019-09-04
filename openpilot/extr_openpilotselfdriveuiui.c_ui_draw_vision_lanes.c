#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  model_path_vertices_data ;
struct TYPE_14__ {int /*<<< orphan*/  prob; } ;
struct TYPE_11__ {TYPE_6__ right_lane; TYPE_6__ left_lane; } ;
struct TYPE_13__ {scalar_t__ engaged; TYPE_1__ model; } ;
struct TYPE_12__ {int model_changed; int livempc_or_live20_changed; int /*<<< orphan*/ * track_vertices; int /*<<< orphan*/ * model_path_vertices; TYPE_3__ scene; } ;
typedef  TYPE_2__ UIState ;
typedef  TYPE_3__ UIScene ;

/* Variables and functions */
 int MODEL_LANE_PATH_CNT ; 
 int /*<<< orphan*/  nvgRGBAf (double,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_draw_lane (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_draw_track (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_all_lane_lines_data (TYPE_2__*,TYPE_6__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_all_track_data (TYPE_2__*) ; 

__attribute__((used)) static void ui_draw_vision_lanes(UIState *s) {
  const UIScene *scene = &s->scene;
  model_path_vertices_data *pvd = &s->model_path_vertices[0];
  if(s->model_changed) {
    update_all_lane_lines_data(s, scene->model.left_lane, pvd);
    update_all_lane_lines_data(s, scene->model.right_lane, pvd + MODEL_LANE_PATH_CNT);
    s->model_changed = false;
  }
  // Draw left lane edge
  ui_draw_lane(
      s, &scene->model.left_lane,
      pvd,
      nvgRGBAf(1.0, 1.0, 1.0, scene->model.left_lane.prob));

  // Draw right lane edge
  ui_draw_lane(
      s, &scene->model.right_lane,
      pvd + MODEL_LANE_PATH_CNT,
      nvgRGBAf(1.0, 1.0, 1.0, scene->model.right_lane.prob));

  if(s->livempc_or_live20_changed) {
    update_all_track_data(s);
    s->livempc_or_live20_changed = false;
  }
  // Draw vision path
  ui_draw_track(s, false, &s->track_vertices[0]);
  if (scene->engaged) {
    // Draw MPC path when engaged
    ui_draw_track(s, true, &s->track_vertices[1]);
  }
}