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
typedef  int mrb_int ;

/* Variables and functions */
 struct RString* RSTRING (int /*<<< orphan*/ ) ; 
 int RSTR_LEN (struct RString*) ; 
 char* RSTR_PTR (struct RString*) ; 
 int /*<<< orphan*/  RSTR_SET_LEN (struct RString*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mrb_str_modify (int /*<<< orphan*/ *,struct RString*) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static mrb_value
io_bufread(mrb_state *mrb, mrb_value self)
{
  mrb_value str, str2;
  mrb_int len, newlen;
  struct RString *s;
  char *p;

  mrb_get_args(mrb, "Si", &str, &len);
  s = RSTRING(str);
  mrb_str_modify(mrb, s);
  p = RSTR_PTR(s);
  str2 = mrb_str_new(mrb, p, len);
  newlen = RSTR_LEN(s)-len;
  memmove(p, p+len, newlen);
  p[newlen] = '\0';
  RSTR_SET_LEN(s, newlen);

  return str2;
}