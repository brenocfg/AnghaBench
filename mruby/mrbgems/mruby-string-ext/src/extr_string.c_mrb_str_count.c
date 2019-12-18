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

/* Variables and functions */
 size_t RSTRING_LEN (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 struct tr_pattern STATIC_TR_PATTERN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mrb_fixnum_value (size_t) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 scalar_t__ tr_bitmap_detect (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  tr_compile_pattern (struct tr_pattern*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr_free_pattern (int /*<<< orphan*/ *,struct tr_pattern*) ; 
 int /*<<< orphan*/  tr_parse_pattern (int /*<<< orphan*/ *,struct tr_pattern*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_str_count(mrb_state *mrb, mrb_value str)
{
  mrb_value v_pat = mrb_nil_value();
  mrb_int i;
  char *s;
  mrb_int len;
  mrb_int count = 0;
  struct tr_pattern pat = STATIC_TR_PATTERN;
  uint8_t bitmap[32];

  mrb_get_args(mrb, "S", &v_pat);
  tr_parse_pattern(mrb, &pat, v_pat, TRUE);
  tr_compile_pattern(&pat, v_pat, bitmap);
  tr_free_pattern(mrb, &pat);

  s = RSTRING_PTR(str);
  len = RSTRING_LEN(str);
  for (i = 0; i < len; i++) {
    if (tr_bitmap_detect(bitmap, s[i])) count++;
  }
  return mrb_fixnum_value(count);
}