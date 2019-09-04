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
struct cereal_ModelData_PathData {int /*<<< orphan*/  std; int /*<<< orphan*/  prob; int /*<<< orphan*/  points; } ;
struct capn_segment {int dummy; } ;
typedef  int /*<<< orphan*/  cereal_ModelData_PathData_ptr ;
typedef  int /*<<< orphan*/  capn_list32 ;
struct TYPE_3__ {int /*<<< orphan*/  std; int /*<<< orphan*/  prob; int /*<<< orphan*/ * points; } ;
typedef  TYPE_1__ PathData ;

/* Variables and functions */
 int MODEL_PATH_DISTANCE ; 
 int /*<<< orphan*/  capn_from_f32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capn_new_list32 (struct capn_segment*,int) ; 
 int /*<<< orphan*/  capn_set32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cereal_new_ModelData_PathData (struct capn_segment*) ; 
 int /*<<< orphan*/  cereal_write_ModelData_PathData (struct cereal_ModelData_PathData*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cereal_ModelData_PathData_ptr path_to_cereal(struct capn_segment *cs, const PathData data) {
  capn_list32 points_ptr = capn_new_list32(cs, MODEL_PATH_DISTANCE);
  for (int i=0; i<MODEL_PATH_DISTANCE; i++) {
    capn_set32(points_ptr, i, capn_from_f32(data.points[i]));
  }

  cereal_ModelData_PathData_ptr ret = cereal_new_ModelData_PathData(cs);
  struct cereal_ModelData_PathData d = {
    .points = points_ptr,
    .prob = data.prob,
    .std = data.std,
  };
  cereal_write_ModelData_PathData(&d, ret);
  return ret;
}