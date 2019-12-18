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
struct RBasic {scalar_t__ tt; struct RBasic* gcnext; } ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {struct RBasic* gray_list; } ;
typedef  TYPE_1__ mrb_gc ;

/* Variables and functions */
 scalar_t__ MRB_TT_MAXDEFINE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  paint_gray (struct RBasic*) ; 

__attribute__((used)) static inline void
add_gray_list(mrb_state *mrb, mrb_gc *gc, struct RBasic *obj)
{
#ifdef MRB_GC_STRESS
  if (obj->tt > MRB_TT_MAXDEFINE) {
    abort();
  }
#endif
  paint_gray(obj);
  obj->gcnext = gc->gray_list;
  gc->gray_list = obj;
}