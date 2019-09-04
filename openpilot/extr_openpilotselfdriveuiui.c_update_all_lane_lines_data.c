#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  model_path_vertices_data ;
typedef  int /*<<< orphan*/  UIState ;
struct TYPE_3__ {double prob; int /*<<< orphan*/  points; int /*<<< orphan*/  std; } ;
typedef  TYPE_1__ PathData ;

/* Variables and functions */
 float min (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  update_lane_line_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_all_lane_lines_data(UIState *s, const PathData path, model_path_vertices_data *pstart) {
  update_lane_line_data(s, path.points, 0.025*path.prob, false, pstart);
  float var = min(path.std, 0.7);
  update_lane_line_data(s, path.points, -var, true, pstart + 1);
  update_lane_line_data(s, path.points, var, true, pstart + 2);
}