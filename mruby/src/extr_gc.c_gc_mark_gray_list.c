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
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_6__ {TYPE_2__* gray_list; } ;
typedef  TYPE_1__ mrb_gc ;
struct TYPE_7__ {struct TYPE_7__* gcnext; } ;

/* Variables and functions */
 int /*<<< orphan*/  gc_mark_children (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ is_gray (TYPE_2__*) ; 

__attribute__((used)) static void
gc_mark_gray_list(mrb_state *mrb, mrb_gc *gc) {
  while (gc->gray_list) {
    if (is_gray(gc->gray_list))
      gc_mark_children(mrb, gc, gc->gray_list);
    else
      gc->gray_list = gc->gray_list->gcnext;
  }
}