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
struct tmpl {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  mrb_float ;

/* Variables and functions */
 int /*<<< orphan*/  E_RANGE_ERROR ; 
 int /*<<< orphan*/  E_TYPE_ERROR ; 
#define  PACK_DIR_BASE64 137 
#define  PACK_DIR_CHAR 136 
#define  PACK_DIR_DOUBLE 135 
#define  PACK_DIR_FLOAT 134 
#define  PACK_DIR_HEX 133 
 int PACK_DIR_INVALID ; 
#define  PACK_DIR_LONG 132 
 int PACK_DIR_NUL ; 
#define  PACK_DIR_QUAD 131 
#define  PACK_DIR_SHORT 130 
#define  PACK_DIR_STR 129 
#define  PACK_DIR_UTF8 128 
 unsigned int PACK_FLAG_WIDTH ; 
 int PACK_TYPE_FLOAT ; 
 int PACK_TYPE_INTEGER ; 
 int PACK_TYPE_STRING ; 
 scalar_t__ RARRAY_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ has_tmpl (struct tmpl*) ; 
 int /*<<< orphan*/  mrb_ary_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrb_float_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_to_flo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pack_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int pack_c (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int pack_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int pack_float (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int pack_h (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int pack_l (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int pack_m (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int pack_q (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int pack_s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int pack_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 scalar_t__ pack_x (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int /*<<< orphan*/  prepare_tmpl (int /*<<< orphan*/ *,struct tmpl*) ; 
 int /*<<< orphan*/  read_tmpl (int /*<<< orphan*/ *,struct tmpl*,int*,int*,int*,int*,unsigned int*) ; 

__attribute__((used)) static mrb_value
mrb_pack_pack(mrb_state *mrb, mrb_value ary)
{
  mrb_value o, result;
  mrb_int aidx;
  struct tmpl tmpl;
  int count;
  unsigned int flags;
  int dir, ridx, size, type;

  prepare_tmpl(mrb, &tmpl);

  result = mrb_str_new(mrb, NULL, 128);  /* allocate initial buffer */
  aidx = 0;
  ridx = 0;
  while (has_tmpl(&tmpl)) {
    read_tmpl(mrb, &tmpl, &dir, &type, &size, &count, &flags);

    if (dir == PACK_DIR_INVALID)
      continue;
    else if (dir == PACK_DIR_NUL) {
        ridx += pack_x(mrb, mrb_nil_value(), result, ridx, count, flags);
        continue;
    }

    for (; aidx < RARRAY_LEN(ary); aidx++) {
      if (count == 0 && !(flags & PACK_FLAG_WIDTH))
        break;

      o = mrb_ary_ref(mrb, ary, aidx);
      if (type == PACK_TYPE_INTEGER) {
        o = mrb_to_int(mrb, o);
      }
#ifndef MRB_WITHOUT_FLOAT
      else if (type == PACK_TYPE_FLOAT) {
        if (!mrb_float_p(o)) {
          mrb_float f = mrb_to_flo(mrb, o);
          o = mrb_float_value(mrb, f);
        }
      }
#endif
      else if (type == PACK_TYPE_STRING) {
        if (!mrb_string_p(o)) {
          mrb_raisef(mrb, E_TYPE_ERROR, "can't convert %T into String", o);
        }
      }

      switch (dir) {
      case PACK_DIR_CHAR:
        ridx += pack_c(mrb, o, result, ridx, flags);
        break;
      case PACK_DIR_SHORT:
        ridx += pack_s(mrb, o, result, ridx, flags);
        break;
      case PACK_DIR_LONG:
        ridx += pack_l(mrb, o, result, ridx, flags);
        break;
      case PACK_DIR_QUAD:
        ridx += pack_q(mrb, o, result, ridx, flags);
        break;
      case PACK_DIR_BASE64:
        ridx += pack_m(mrb, o, result, ridx, count, flags);
        break;
      case PACK_DIR_HEX:
        ridx += pack_h(mrb, o, result, ridx, count, flags);
        break;
      case PACK_DIR_STR:
        ridx += pack_a(mrb, o, result, ridx, count, flags);
        break;
#ifndef MRB_WITHOUT_FLOAT
      case PACK_DIR_DOUBLE:
        ridx += pack_double(mrb, o, result, ridx, flags);
        break;
      case PACK_DIR_FLOAT:
        ridx += pack_float(mrb, o, result, ridx, flags);
        break;
#endif
      case PACK_DIR_UTF8:
        ridx += pack_utf8(mrb, o, result, ridx, count, flags);
        break;
      default:
        break;
      }
      if (dir == PACK_DIR_STR || dir == PACK_DIR_BASE64) { /* always consumes 1 entry */
        aidx++;
        break;
      }
      if (count > 0) {
        count--;
      }
    }
    if (ridx < 0) {
      mrb_raise(mrb, E_RANGE_ERROR, "negative (or overflowed) template size");
    }
  }

  mrb_str_resize(mrb, result, ridx);
  return result;
}