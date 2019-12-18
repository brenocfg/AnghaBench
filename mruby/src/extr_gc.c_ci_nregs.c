#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* irep; } ;
struct RProc {TYPE_2__ body; } ;
struct TYPE_7__ {int argc; struct RProc* proc; } ;
typedef  TYPE_3__ mrb_callinfo ;
struct TYPE_5__ {int nregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_PROC_CFUNC_P (struct RProc*) ; 

__attribute__((used)) static int
ci_nregs(mrb_callinfo *ci)
{
  struct RProc *p = ci->proc;
  int n = 0;

  if (!p) {
    if (ci->argc < 0) return 3;
    return ci->argc+2;
  }
  if (!MRB_PROC_CFUNC_P(p) && p->body.irep) {
    n = p->body.irep->nregs;
  }
  if (ci->argc < 0) {
    if (n < 3) n = 3; /* self + args + blk */
  }
  if (ci->argc > n) {
    n = ci->argc + 2; /* self + blk */
  }
  return n;
}