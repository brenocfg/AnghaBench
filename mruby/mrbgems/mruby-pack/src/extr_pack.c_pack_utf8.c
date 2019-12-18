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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_RANGE_ERROR ; 
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  str_len_ensure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
pack_utf8(mrb_state *mrb, mrb_value o, mrb_value str, mrb_int sidx, long count, unsigned int flags)
{
  char utf8[4];
  int len = 0;
  uint32_t c = 0;

  c = (uint32_t)mrb_fixnum(o);

  /* Unicode character */
  /* from mruby-compiler gem */
  if (c < 0x80) {
    utf8[0] = (char)c;
    len = 1;
  }
  else if (c < 0x800) {
    utf8[0] = (char)(0xC0 | (c >> 6));
    utf8[1] = (char)(0x80 | (c & 0x3F));
    len = 2;
  }
  else if (c < 0x10000) {
    utf8[0] = (char)(0xE0 |  (c >> 12)        );
    utf8[1] = (char)(0x80 | ((c >>  6) & 0x3F));
    utf8[2] = (char)(0x80 | ( c        & 0x3F));
    len = 3;
  }
  else if (c < 0x200000) {
    utf8[0] = (char)(0xF0 |  (c >> 18)        );
    utf8[1] = (char)(0x80 | ((c >> 12) & 0x3F));
    utf8[2] = (char)(0x80 | ((c >>  6) & 0x3F));
    utf8[3] = (char)(0x80 | ( c        & 0x3F));
    len = 4;
  }
  else {
    mrb_raise(mrb, E_RANGE_ERROR, "pack(U): value out of range");
  }

  str = str_len_ensure(mrb, str, sidx + len);
  memcpy(RSTRING_PTR(str) + sidx, utf8, len);

  return len;
}