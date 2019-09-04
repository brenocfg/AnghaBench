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
struct TYPE_7__ {unsigned long long model_ts; float lead_d_rel; float lead_v_rel; int /*<<< orphan*/  lead_y_rel; scalar_t__ lead_status; int /*<<< orphan*/  world_objects_visible; } ;
struct TYPE_6__ {TYPE_2__ scene; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;

/* Variables and functions */
 int /*<<< orphan*/  draw_chevron (TYPE_1__*,double,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ min (float,int) ; 
 unsigned long long nanos_since_boot () ; 
 int /*<<< orphan*/  nvgRGBA (int,int,int,int) ; 
 int /*<<< orphan*/  ui_draw_vision_lanes (TYPE_1__*) ; 

__attribute__((used)) static void ui_draw_world(UIState *s) {
  const UIScene *scene = &s->scene;
  if (!scene->world_objects_visible) {
    return;
  }

  if ((nanos_since_boot() - scene->model_ts) < 1000000000ULL) {
    // Draw lane edges and vision/mpc tracks
    ui_draw_vision_lanes(s);
  }

  if (scene->lead_status) {
    // Draw lead car indicator
    float fillAlpha = 0;
    float speedBuff = 10.;
    float leadBuff = 40.;
    if (scene->lead_d_rel < leadBuff) {
      fillAlpha = 255*(1.0-(scene->lead_d_rel/leadBuff));
      if (scene->lead_v_rel < 0) {
        fillAlpha += 255*(-1*(scene->lead_v_rel/speedBuff));
      }
      fillAlpha = (int)(min(fillAlpha, 255));
    }
    draw_chevron(s, scene->lead_d_rel+2.7, scene->lead_y_rel, 25,
                  nvgRGBA(201, 34, 49, fillAlpha), nvgRGBA(218, 202, 37, 255));
  }
}