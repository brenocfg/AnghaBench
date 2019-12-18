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
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_INDEX_ERROR ; 
 scalar_t__ RSTRING_CHAR_LEN (int /*<<< orphan*/ ) ; 
#define  STR_BYTE_RANGE_CORRECTED 131 
#define  STR_CHAR_RANGE 130 
#define  STR_CHAR_RANGE_CORRECTED 129 
#define  STR_OUT_OF_RANGE 128 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int str_convert_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  str_out_of_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_range_to_bytes (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  str_replace_partial (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mrb_str_aset(mrb_state *mrb, mrb_value str, mrb_value indx, mrb_value alen, mrb_value replace)
{
  mrb_int beg, len, charlen;

  mrb_to_str(mrb, replace);

  switch (str_convert_range(mrb, str, indx, alen, &beg, &len)) {
    case STR_OUT_OF_RANGE:
    default:
      mrb_raise(mrb, E_INDEX_ERROR, "string not matched");
    case STR_CHAR_RANGE:
      if (len < 0) {
        mrb_raisef(mrb, E_INDEX_ERROR, "negative length %v", alen);
      }
      charlen = RSTRING_CHAR_LEN(str);
      if (beg < 0) { beg += charlen; }
      if (beg < 0 || beg > charlen) { str_out_of_index(mrb, indx); }
      /* fall through */
    case STR_CHAR_RANGE_CORRECTED:
      str_range_to_bytes(str, &beg, &len);
      /* fall through */
    case STR_BYTE_RANGE_CORRECTED:
      str_replace_partial(mrb, str, beg, beg + len, replace);
  }
}