#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_6__ {int line_type; int /*<<< orphan*/  line_entry_count; } ;
typedef  TYPE_2__ mrb_irep_debug_info_file ;
struct TYPE_7__ {int rlen; struct TYPE_7__** reps; TYPE_1__* debug_info; } ;
typedef  TYPE_3__ mrb_irep ;
struct TYPE_5__ {size_t flen; TYPE_2__** files; } ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_assert (int /*<<< orphan*/ ) ; 
#define  mrb_debug_line_ary 129 
#define  mrb_debug_line_flat_map 128 

__attribute__((used)) static size_t
get_debug_record_size(mrb_state *mrb, mrb_irep *irep)
{
  size_t ret = 0;
  uint16_t f_idx;
  int i;

  ret += sizeof(uint32_t); /* record size */
  ret += sizeof(uint16_t); /* file count */

  for (f_idx = 0; f_idx < irep->debug_info->flen; ++f_idx) {
    mrb_irep_debug_info_file const* file = irep->debug_info->files[f_idx];

    ret += sizeof(uint32_t); /* position */
    ret += sizeof(uint16_t); /* filename index */

    /* lines */
    ret += sizeof(uint32_t); /* entry count */
    ret += sizeof(uint8_t); /* line type */
    switch (file->line_type) {
      case mrb_debug_line_ary:
        ret += sizeof(uint16_t) * (size_t)(file->line_entry_count);
        break;

      case mrb_debug_line_flat_map:
        ret += (sizeof(uint32_t) + sizeof(uint16_t)) * (size_t)(file->line_entry_count);
        break;

      default: mrb_assert(0); break;
    }
  }
  for (i=0; i<irep->rlen; i++) {
    ret += get_debug_record_size(mrb, irep->reps[i]);
  }

  return ret;
}