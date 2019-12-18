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
struct mrb_complex {void* imaginary; void* real; } ;
struct RClass {int dummy; } ;
struct RBasic {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  void* mrb_float ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_SET_FROZEN_FLAG (struct RBasic*) ; 
 struct RBasic* complex_alloc (int /*<<< orphan*/ *,struct RClass*,struct mrb_complex**) ; 
 struct RClass* mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RBasic*) ; 

__attribute__((used)) static mrb_value
complex_new(mrb_state *mrb, mrb_float real, mrb_float imaginary)
{
  struct RClass *c = mrb_class_get(mrb, "Complex");
  struct mrb_complex *p;
  struct RBasic *comp = complex_alloc(mrb, c, &p);
  p->real = real;
  p->imaginary = imaginary;
  MRB_SET_FROZEN_FLAG(comp);

  return mrb_obj_value(comp);
}