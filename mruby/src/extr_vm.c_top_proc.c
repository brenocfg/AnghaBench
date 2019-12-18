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
struct RProc {struct RProc* upper; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ MRB_PROC_SCOPE_P (struct RProc*) ; 
 scalar_t__ MRB_PROC_STRICT_P (struct RProc*) ; 

__attribute__((used)) static inline struct RProc*
top_proc(mrb_state *mrb, struct RProc *proc)
{
  while (proc->upper) {
    if (MRB_PROC_SCOPE_P(proc) || MRB_PROC_STRICT_P(proc))
      return proc;
    proc = proc->upper;
  }
  return proc;
}