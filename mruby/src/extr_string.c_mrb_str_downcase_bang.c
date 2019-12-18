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
typedef  scalar_t__ mrb_bool ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ISUPPER (char) ; 
 int RSTR_LEN (struct RString*) ; 
 char* RSTR_PTR (struct RString*) ; 
 char TOLOWER (char) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_modify_keep_ascii (int /*<<< orphan*/ *,struct RString*) ; 
 struct RString* mrb_str_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_str_downcase_bang(mrb_state *mrb, mrb_value str)
{
  char *p, *pend;
  mrb_bool modify = FALSE;
  struct RString *s = mrb_str_ptr(str);

  mrb_str_modify_keep_ascii(mrb, s);
  p = RSTR_PTR(s);
  pend = RSTR_PTR(s) + RSTR_LEN(s);
  while (p < pend) {
    if (ISUPPER(*p)) {
      *p = TOLOWER(*p);
      modify = TRUE;
    }
    p++;
  }

  if (modify) return str;
  return mrb_nil_value();
}