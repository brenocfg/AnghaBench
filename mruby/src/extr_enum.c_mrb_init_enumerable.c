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
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  enum_update_hash ; 
 struct RClass* mrb_define_module (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_define_module_function (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mrb_init_enumerable(mrb_state *mrb)
{
  struct RClass *enumerable;
  enumerable = mrb_define_module(mrb, "Enumerable");  /* 15.3.2 */
  mrb_define_module_function(mrb, enumerable, "__update_hash", enum_update_hash, MRB_ARGS_REQ(3));
}