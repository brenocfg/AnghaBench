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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;

/* Variables and functions */
 char* RSTRING_CSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VF_FORMAT0 (char const*) ; 
 int /*<<< orphan*/  VF_FORMAT1 (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VF_FORMAT2 (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VF_FORMAT_INIT (int /*<<< orphan*/ ) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value
vf_s_format(mrb_state *mrb, mrb_value klass)
{
  mrb_value fmt_str, args[2];
  mrb_int argc = mrb_get_args(mrb, "S|oo", &fmt_str, args, args+1);
  const char *fmt = RSTRING_CSTR(mrb, fmt_str);

  VF_FORMAT_INIT(klass);

  switch (argc) {
    case 1: return VF_FORMAT0(fmt);
    case 2: return VF_FORMAT1(fmt, args);
    case 3: return VF_FORMAT2(fmt, args);
    default: return mrb_nil_value();  /* not reached */
  }
}