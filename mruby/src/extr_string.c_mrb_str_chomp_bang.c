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
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 size_t RSTR_LEN (struct RString*) ; 
 char* RSTR_PTR (struct RString*) ; 
 int /*<<< orphan*/  RSTR_SET_LEN (struct RString*,scalar_t__) ; 
 scalar_t__ memcmp (scalar_t__*,char*,scalar_t__) ; 
 scalar_t__ mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_modify_keep_ascii (int /*<<< orphan*/ *,struct RString*) ; 
 struct RString* mrb_str_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_str_chomp_bang(mrb_state *mrb, mrb_value str)
{
  mrb_value rs;
  mrb_int newline;
  char *p, *pp;
  mrb_int rslen;
  mrb_int len;
  mrb_int argc;
  struct RString *s = mrb_str_ptr(str);

  argc = mrb_get_args(mrb, "|S", &rs);
  mrb_str_modify_keep_ascii(mrb, s);
  len = RSTR_LEN(s);
  if (argc == 0) {
    if (len == 0) return mrb_nil_value();
  smart_chomp:
    if (RSTR_PTR(s)[len-1] == '\n') {
      RSTR_SET_LEN(s, RSTR_LEN(s) - 1);
      if (RSTR_LEN(s) > 0 &&
          RSTR_PTR(s)[RSTR_LEN(s)-1] == '\r') {
        RSTR_SET_LEN(s, RSTR_LEN(s) - 1);
      }
    }
    else if (RSTR_PTR(s)[len-1] == '\r') {
      RSTR_SET_LEN(s, RSTR_LEN(s) - 1);
    }
    else {
      return mrb_nil_value();
    }
    RSTR_PTR(s)[RSTR_LEN(s)] = '\0';
    return str;
  }

  if (len == 0 || mrb_nil_p(rs)) return mrb_nil_value();
  p = RSTR_PTR(s);
  rslen = RSTRING_LEN(rs);
  if (rslen == 0) {
    while (len>0 && p[len-1] == '\n') {
      len--;
      if (len>0 && p[len-1] == '\r')
        len--;
    }
    if (len < RSTR_LEN(s)) {
      RSTR_SET_LEN(s, len);
      p[len] = '\0';
      return str;
    }
    return mrb_nil_value();
  }
  if (rslen > len) return mrb_nil_value();
  newline = RSTRING_PTR(rs)[rslen-1];
  if (rslen == 1 && newline == '\n')
    newline = RSTRING_PTR(rs)[rslen-1];
  if (rslen == 1 && newline == '\n')
    goto smart_chomp;

  pp = p + len - rslen;
  if (p[len-1] == newline &&
     (rslen <= 1 ||
     memcmp(RSTRING_PTR(rs), pp, rslen) == 0)) {
    RSTR_SET_LEN(s, len - rslen);
    p[RSTR_LEN(s)] = '\0';
    return str;
  }
  return mrb_nil_value();
}