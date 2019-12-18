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
struct RProc {int dummy; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_method_t ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_METHOD_FUNC (int /*<<< orphan*/ ) ; 
 struct RProc* MRB_METHOD_PROC (int /*<<< orphan*/ ) ; 
 scalar_t__ MRB_METHOD_PROC_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MRB_METHOD_UNDEF_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_method_search_vm (int /*<<< orphan*/ *,struct RClass**,int /*<<< orphan*/ ) ; 
 struct RProc* mrb_proc_new_cfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct RProc *
method_search_vm(mrb_state *mrb, struct RClass **cp, mrb_sym mid)
{
  mrb_method_t m = mrb_method_search_vm(mrb, cp, mid);
  if (MRB_METHOD_UNDEF_P(m))
    return NULL;
  if (MRB_METHOD_PROC_P(m))
    return MRB_METHOD_PROC(m);
  return mrb_proc_new_cfunc(mrb, MRB_METHOD_FUNC(m));
}