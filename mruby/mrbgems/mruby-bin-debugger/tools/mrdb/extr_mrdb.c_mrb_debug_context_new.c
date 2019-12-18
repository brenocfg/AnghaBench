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
struct TYPE_4__ {int next_bpno; int /*<<< orphan*/  xphase; int /*<<< orphan*/  xm; } ;
typedef  TYPE_1__ mrb_debug_context ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_INIT ; 
 int /*<<< orphan*/  DBG_PHASE_BEFORE_RUN ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static mrb_debug_context*
mrb_debug_context_new(mrb_state *mrb)
{
  mrb_debug_context *dbg = (mrb_debug_context*)mrb_malloc(mrb, sizeof(mrb_debug_context));

  memset(dbg, 0, sizeof(mrb_debug_context));

  dbg->xm = DBG_INIT;
  dbg->xphase = DBG_PHASE_BEFORE_RUN;
  dbg->next_bpno = 1;

  return dbg;
}