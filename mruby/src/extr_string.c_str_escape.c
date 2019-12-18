#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  scalar_t__ mrb_bool ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ ISPRINT (unsigned char) ; 
 scalar_t__ IS_EVSTR (char const*,char const*) ; 
 int /*<<< orphan*/  MRB_STR_ASCII ; 
 char* RSTRING_END (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTR_SET_ASCII_FLAG (TYPE_1__*) ; 
 char* mrb_digitmap ; 
 int /*<<< orphan*/  mrb_str_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mrb_str_cat_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* mrb_str_ptr (int /*<<< orphan*/ ) ; 
 int utf8len (char const*,char const*) ; 

__attribute__((used)) static mrb_value
str_escape(mrb_state *mrb, mrb_value str, mrb_bool inspect)
{
  const char *p, *pend;
  char buf[4];  /* `\x??` or UTF-8 character */
  mrb_value result = mrb_str_new_lit(mrb, "\"");
#ifdef MRB_UTF8_STRING
  uint32_t ascii_flag = MRB_STR_ASCII;
#endif

  p = RSTRING_PTR(str); pend = RSTRING_END(str);
  for (;p < pend; p++) {
    unsigned char c, cc;
#ifdef MRB_UTF8_STRING
    if (inspect) {
      mrb_int clen = utf8len(p, pend);
      if (clen > 1) {
        mrb_int i;

        for (i=0; i<clen; i++) {
          buf[i] = p[i];
        }
        mrb_str_cat(mrb, result, buf, clen);
        p += clen-1;
        ascii_flag = 0;
        continue;
      }
    }
#endif
    c = *p;
    if (c == '"'|| c == '\\' || (c == '#' && IS_EVSTR(p+1, pend))) {
      buf[0] = '\\'; buf[1] = c;
      mrb_str_cat(mrb, result, buf, 2);
      continue;
    }
    if (ISPRINT(c)) {
      buf[0] = c;
      mrb_str_cat(mrb, result, buf, 1);
      continue;
    }
    switch (c) {
      case '\n': cc = 'n'; break;
      case '\r': cc = 'r'; break;
      case '\t': cc = 't'; break;
      case '\f': cc = 'f'; break;
      case '\013': cc = 'v'; break;
      case '\010': cc = 'b'; break;
      case '\007': cc = 'a'; break;
      case 033: cc = 'e'; break;
      default: cc = 0; break;
    }
    if (cc) {
      buf[0] = '\\';
      buf[1] = (char)cc;
      mrb_str_cat(mrb, result, buf, 2);
      continue;
    }
    else {
      buf[0] = '\\';
      buf[1] = 'x';
      buf[3] = mrb_digitmap[c % 16]; c /= 16;
      buf[2] = mrb_digitmap[c % 16];
      mrb_str_cat(mrb, result, buf, 4);
      continue;
    }
  }
  mrb_str_cat_lit(mrb, result, "\"");
#ifdef MRB_UTF8_STRING
  if (inspect) {
    mrb_str_ptr(str)->flags |= ascii_flag;
    mrb_str_ptr(result)->flags |= ascii_flag;
  }
  else {
    RSTR_SET_ASCII_FLAG(mrb_str_ptr(result));
  }
#endif

  return result;
}