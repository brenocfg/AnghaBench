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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 scalar_t__ get_lv_record_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_sym_name_len (int /*<<< orphan*/ *,int /*<<< orphan*/  const,scalar_t__*) ; 

__attribute__((used)) static size_t
get_lv_section_size(mrb_state *mrb, mrb_irep *irep, mrb_sym const *syms, uint32_t syms_len)
{
  size_t ret = 0, i;

  ret += sizeof(uint32_t); /* syms_len */
  ret += sizeof(uint16_t) * syms_len; /* symbol name lengths */
  for (i = 0; i < syms_len; ++i) {
    mrb_int str_len;
    mrb_sym_name_len(mrb, syms[i], &str_len);
    ret += str_len;
  }

  ret += get_lv_record_size(mrb, irep);

  return ret;
}