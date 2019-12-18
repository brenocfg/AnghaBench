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

/* Variables and functions */
 int mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_str_aset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_undef_value () ; 

__attribute__((used)) static mrb_value
mrb_str_aset_m(mrb_state *mrb, mrb_value str)
{
  mrb_value indx, alen, replace;

  switch (mrb_get_args(mrb, "oo|S!", &indx, &alen, &replace)) {
    case 2:
      replace = alen;
      alen = mrb_undef_value();
      break;
    case 3:
      break;
  }
  mrb_str_aset(mrb, str, indx, alen, replace);
  return str;
}