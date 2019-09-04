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
typedef  int /*<<< orphan*/  model_path_vertices_data ;
typedef  int /*<<< orphan*/  UIState ;
struct TYPE_7__ {int a; } ;
struct TYPE_6__ {int /*<<< orphan*/  std; } ;
typedef  TYPE_1__ PathData ;
typedef  TYPE_2__ NVGcolor ;

/* Variables and functions */
 float min (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  ui_draw_lane_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__) ; 

__attribute__((used)) static void ui_draw_lane(UIState *s, const PathData *path, model_path_vertices_data *pstart, NVGcolor color) {
  ui_draw_lane_line(s, pstart, color);
  float var = min(path->std, 0.7);
  color.a /= 4;
  ui_draw_lane_line(s, pstart + 1, color);
  ui_draw_lane_line(s, pstart + 2, color);
}