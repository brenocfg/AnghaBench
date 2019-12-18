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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {scalar_t__ bpnum; int /*<<< orphan*/  bp; } ;
typedef  TYPE_1__ mrb_debug_context ;
typedef  int /*<<< orphan*/  mrb_debug_breakpoint ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MRB_DEBUG_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int32_t
mrb_debug_get_break_all(mrb_state *mrb, mrb_debug_context *dbg, uint32_t size, mrb_debug_breakpoint *bp)
{
  uint32_t get_size = 0;

  if ((mrb == NULL) || (dbg == NULL) || (bp == NULL)) {
    return MRB_DEBUG_INVALID_ARGUMENT;
  }

  if (dbg->bpnum >= size) {
    get_size = size;
  }
  else {
    get_size = dbg->bpnum;
  }

  memcpy(bp, dbg->bp, sizeof(mrb_debug_breakpoint) * get_size);

  return get_size;
}