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
struct TYPE_4__ {int /*<<< orphan*/  string_class; int /*<<< orphan*/  array_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  check_little_endian () ; 
 int /*<<< orphan*/  make_base64_dec_tab () ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_pack_pack ; 
 int /*<<< orphan*/  mrb_pack_unpack ; 
 int /*<<< orphan*/  mrb_pack_unpack1 ; 

void
mrb_mruby_pack_gem_init(mrb_state *mrb)
{
  check_little_endian();
  make_base64_dec_tab();

  mrb_define_method(mrb, mrb->array_class, "pack", mrb_pack_pack, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb->string_class, "unpack", mrb_pack_unpack, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb->string_class, "unpack1", mrb_pack_unpack1, MRB_ARGS_REQ(1));
}