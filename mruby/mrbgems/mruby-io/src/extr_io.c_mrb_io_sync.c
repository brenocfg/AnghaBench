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
struct mrb_io {int /*<<< orphan*/  sync; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 struct mrb_io* io_get_open_fptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_bool_value (int /*<<< orphan*/ ) ; 

mrb_value
mrb_io_sync(mrb_state *mrb, mrb_value self)
{
  struct mrb_io *fptr;
  fptr = io_get_open_fptr(mrb, self);
  return mrb_bool_value(fptr->sync);
}