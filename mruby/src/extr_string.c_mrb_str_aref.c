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
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  RSTRING_LEN (int /*<<< orphan*/ ) ; 
#define  STR_BYTE_RANGE_CORRECTED 131 
#define  STR_CHAR_RANGE 130 
#define  STR_CHAR_RANGE_CORRECTED 129 
#define  STR_OUT_OF_RANGE 128 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_byte_subseq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_undef_p (int /*<<< orphan*/ ) ; 
 int str_convert_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  str_subseq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_substr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_str_aref(mrb_state *mrb, mrb_value str, mrb_value indx, mrb_value alen)
{
  mrb_int beg, len;

  switch (str_convert_range(mrb, str, indx, alen, &beg, &len)) {
    case STR_CHAR_RANGE_CORRECTED:
      return str_subseq(mrb, str, beg, len);
    case STR_CHAR_RANGE:
      str = str_substr(mrb, str, beg, len);
      if (mrb_undef_p(alen) && !mrb_nil_p(str) && RSTRING_LEN(str) == 0) return mrb_nil_value();
      return str;
    case STR_BYTE_RANGE_CORRECTED:
      if (mrb_string_p(indx)) {
        return mrb_str_dup(mrb, indx);
      }
      else {
        return mrb_str_byte_subseq(mrb, str, beg, len);
      }
    case STR_OUT_OF_RANGE:
    default:
      return mrb_nil_value();
  }
}