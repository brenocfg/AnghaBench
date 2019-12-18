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
struct RString {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 scalar_t__ MRB_INT_MAX ; 
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTR_LEN (struct RString*) ; 
 char* RSTR_PTR (struct RString*) ; 
 int /*<<< orphan*/  RSTR_SET_LEN (struct RString*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_modify (int /*<<< orphan*/ *,struct RString*) ; 
 struct RString* mrb_str_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resize_capa (int /*<<< orphan*/ *,struct RString*,scalar_t__) ; 
 int /*<<< orphan*/  str_out_of_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
str_replace_partial(mrb_state *mrb, mrb_value src, mrb_int pos, mrb_int end, mrb_value rep)
{
  const mrb_int shrink_threshold = 256;
  struct RString *str = mrb_str_ptr(src);
  mrb_int len = RSTR_LEN(str);
  mrb_int replen, newlen;
  char *strp;

  if (end > len) { end = len; }

  if (pos < 0 || pos > len) {
    str_out_of_index(mrb, mrb_fixnum_value(pos));
  }

  replen = (mrb_nil_p(rep) ? 0 : RSTRING_LEN(rep));
  newlen = replen + len - (end - pos);

  if (newlen >= MRB_INT_MAX || newlen < replen /* overflowed */) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "string size too big");
  }

  mrb_str_modify(mrb, str);

  if (len < newlen) {
    resize_capa(mrb, str, newlen);
  }

  strp = RSTR_PTR(str);

  memmove(strp + newlen - (len - end), strp + end, len - end);
  if (!mrb_nil_p(rep)) {
    memmove(strp + pos, RSTRING_PTR(rep), replen);
  }
  RSTR_SET_LEN(str, newlen);
  strp[newlen] = '\0';

  if (len - newlen >= shrink_threshold) {
    resize_capa(mrb, str, newlen);
  }

  return src;
}