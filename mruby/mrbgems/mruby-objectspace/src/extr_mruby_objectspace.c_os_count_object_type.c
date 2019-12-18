#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct os_count_struct {int /*<<< orphan*/ * counts; int /*<<< orphan*/  freed; int /*<<< orphan*/  total; } ;
struct RBasic {size_t tt; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int MRB_EACH_OBJ_OK ; 
 scalar_t__ mrb_object_dead_p (int /*<<< orphan*/ *,struct RBasic*) ; 

__attribute__((used)) static int
os_count_object_type(mrb_state *mrb, struct RBasic *obj, void *data)
{
  struct os_count_struct *obj_count;
  obj_count = (struct os_count_struct*)data;

  obj_count->total++;

  if (mrb_object_dead_p(mrb, obj)) {
    obj_count->freed++;
  }
  else {
    obj_count->counts[obj->tt]++;
  }
  return MRB_EACH_OBJ_OK;
}