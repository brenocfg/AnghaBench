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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 char* mrb_digitmap ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,char*) ; 
 char* remove_sign_bits (char*,int) ; 

__attribute__((used)) static mrb_value
mrb_fix2binstr(mrb_state *mrb, mrb_value x, int base)
{
  char buf[66], *b = buf + sizeof buf;
  mrb_int num = mrb_fixnum(x);
  uint64_t val = (uint64_t)num;
  char d;

  if (base != 2) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid radix %d", base);
  }
  if (val == 0) {
    return mrb_str_new_lit(mrb, "0");
  }
  *--b = '\0';
  do {
    *--b = mrb_digitmap[(int)(val % base)];
  } while (val /= base);

  if (num < 0) {
    b = remove_sign_bits(b, base);
    switch (base) {
    case 16: d = 'f'; break;
    case 8:  d = '7'; break;
    case 2:  d = '1'; break;
    default: d = 0;   break;
    }

    if (d && *b != d) {
      *--b = d;
    }
  }

  return mrb_str_new_cstr(mrb, b);
}