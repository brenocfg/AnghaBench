#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p; } ;
struct cereal_ModelData_PathData {TYPE_1__ points; int /*<<< orphan*/  std; int /*<<< orphan*/  prob; } ;
typedef  int /*<<< orphan*/  cereal_ModelData_PathData_ptr ;
typedef  TYPE_1__ capn_list32 ;
struct TYPE_6__ {int /*<<< orphan*/ * points; int /*<<< orphan*/  std; int /*<<< orphan*/  prob; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ PathData ;

/* Variables and functions */
 int /*<<< orphan*/  capn_get32 (TYPE_1__,int) ; 
 int /*<<< orphan*/  capn_resolve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capn_to_f32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cereal_read_ModelData_PathData (struct cereal_ModelData_PathData*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PathData read_path(cereal_ModelData_PathData_ptr pathp) {
  PathData ret = {0};

  struct cereal_ModelData_PathData pathd;
  cereal_read_ModelData_PathData(&pathd, pathp);

  ret.prob = pathd.prob;
  ret.std = pathd.std;

  capn_list32 pointl = pathd.points;
  capn_resolve(&pointl.p);
  for (int i = 0; i < 50; i++) {
    ret.points[i] = capn_to_f32(capn_get32(pointl, i));
  }

  return ret;
}