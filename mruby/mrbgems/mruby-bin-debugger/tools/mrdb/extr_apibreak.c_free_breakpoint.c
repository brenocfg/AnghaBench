#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_7__ {int /*<<< orphan*/ * class_name; scalar_t__ method_name; } ;
struct TYPE_6__ {scalar_t__ file; } ;
struct TYPE_8__ {TYPE_2__ methodpoint; TYPE_1__ linepoint; } ;
struct TYPE_9__ {int type; TYPE_3__ point; } ;
typedef  TYPE_4__ mrb_debug_breakpoint ;

/* Variables and functions */
#define  MRB_DEBUG_BPTYPE_LINE 129 
#define  MRB_DEBUG_BPTYPE_METHOD 128 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
free_breakpoint(mrb_state *mrb, mrb_debug_breakpoint *bp)
{
  switch(bp->type) {
    case MRB_DEBUG_BPTYPE_LINE:
      mrb_free(mrb, (void*)bp->point.linepoint.file);
      break;
    case MRB_DEBUG_BPTYPE_METHOD:
      mrb_free(mrb, (void*)bp->point.methodpoint.method_name);
      if (bp->point.methodpoint.class_name != NULL) {
        mrb_free(mrb, (void*)bp->point.methodpoint.class_name);
      }
      break;
    default:
      break;
  }
}