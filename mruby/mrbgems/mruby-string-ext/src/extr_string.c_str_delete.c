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
typedef  int /*<<< orphan*/  uint8_t ;
struct tr_pattern {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;
typedef  scalar_t__ mrb_bool ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  RSTRING (int /*<<< orphan*/ ) ; 
 size_t RSTRING_LEN (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTR_SET_LEN (int /*<<< orphan*/ ,size_t) ; 
 struct tr_pattern STATIC_TR_PATTERN ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  mrb_str_modify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ tr_bitmap_detect (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  tr_compile_pattern (struct tr_pattern*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr_free_pattern (int /*<<< orphan*/ *,struct tr_pattern*) ; 
 int /*<<< orphan*/  tr_parse_pattern (int /*<<< orphan*/ *,struct tr_pattern*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static mrb_bool
str_delete(mrb_state *mrb, mrb_value str, mrb_value v_pat)
{
  struct tr_pattern pat = STATIC_TR_PATTERN;
  mrb_int i, j;
  char *s;
  mrb_int len;
  mrb_bool flag_changed = FALSE;
  uint8_t bitmap[32];

  mrb_str_modify(mrb, mrb_str_ptr(str));
  tr_parse_pattern(mrb, &pat, v_pat, TRUE);
  tr_compile_pattern(&pat, v_pat, bitmap);
  tr_free_pattern(mrb, &pat);

  s = RSTRING_PTR(str);
  len = RSTRING_LEN(str);

  for (i=j=0; i<len; i++,j++) {
    if (i>j) s[j] = s[i];
    if (tr_bitmap_detect(bitmap, s[i])) {
      flag_changed = TRUE;
      j--;
    }
  }
  if (flag_changed) {
    RSTR_SET_LEN(RSTRING(str), j);
    RSTRING_PTR(str)[j] = 0;
  }
  return flag_changed;
}