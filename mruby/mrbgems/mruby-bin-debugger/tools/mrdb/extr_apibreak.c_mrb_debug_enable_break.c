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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_6__ {TYPE_1__* bp; } ;
typedef  TYPE_2__ mrb_debug_context ;
typedef  size_t int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 size_t MRB_DEBUG_BREAK_INVALID_NO ; 
 size_t MRB_DEBUG_INVALID_ARGUMENT ; 
 size_t MRB_DEBUG_OK ; 
 int /*<<< orphan*/  TRUE ; 
 size_t get_break_index (TYPE_2__*,int /*<<< orphan*/ ) ; 

int32_t
mrb_debug_enable_break(mrb_state *mrb, mrb_debug_context *dbg, uint32_t bpno)
{
  int32_t index = 0;

  if ((mrb == NULL) || (dbg == NULL)) {
    return MRB_DEBUG_INVALID_ARGUMENT;
  }

  index = get_break_index(dbg, bpno);
  if (index == MRB_DEBUG_BREAK_INVALID_NO) {
    return MRB_DEBUG_BREAK_INVALID_NO;
  }

  dbg->bp[index].enable = TRUE;

  return MRB_DEBUG_OK;
}