#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * irep; } ;
struct RProc {TYPE_1__ body; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ MRB_PROC_CFUNC_P (struct RProc*) ; 
 int /*<<< orphan*/  mrb_assoc_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mrb_debug_get_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mrb_debug_get_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 struct RProc* mrb_proc_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static mrb_value
mrb_proc_source_location(mrb_state *mrb, mrb_value self)
{
  struct RProc *p = mrb_proc_ptr(self);

  if (MRB_PROC_CFUNC_P(p)) {
    return mrb_nil_value();
  }
  else {
    mrb_irep *irep = p->body.irep;
    int32_t line;
    const char *filename;

    filename = mrb_debug_get_filename(mrb, irep, 0);
    line = mrb_debug_get_line(mrb, irep, 0);

    return (!filename && line == -1)? mrb_nil_value()
        : mrb_assoc_new(mrb, mrb_str_new_cstr(mrb, filename), mrb_fixnum_value(line));
  }
}