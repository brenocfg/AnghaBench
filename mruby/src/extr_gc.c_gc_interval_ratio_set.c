#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_5__ {int interval_ratio; } ;
struct TYPE_6__ {TYPE_1__ gc; } ;
typedef  TYPE_2__ mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_get_args (TYPE_2__*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value
gc_interval_ratio_set(mrb_state *mrb, mrb_value obj)
{
  mrb_int ratio;

  mrb_get_args(mrb, "i", &ratio);
  mrb->gc.interval_ratio = (int)ratio;
  return mrb_nil_value();
}