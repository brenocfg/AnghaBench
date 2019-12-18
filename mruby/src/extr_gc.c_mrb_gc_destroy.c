#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_4__ {int /*<<< orphan*/  arena; } ;
typedef  TYPE_1__ mrb_gc ;

/* Variables and functions */
 int /*<<< orphan*/  free_heap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrb_gc_destroy(mrb_state *mrb, mrb_gc *gc)
{
  free_heap(mrb, gc);
#ifndef MRB_GC_FIXED_ARENA
  mrb_free(mrb, gc->arena);
#endif
}