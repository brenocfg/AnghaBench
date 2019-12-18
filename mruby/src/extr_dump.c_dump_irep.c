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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct rite_section_lv_header {int dummy; } ;
struct rite_section_irep_header {int dummy; } ;
struct rite_section_debug_header {int dummy; } ;
struct rite_binary_header {int dummy; } ;
struct rite_binary_footer {int dummy; } ;
typedef  int mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  scalar_t__ mrb_bool ;

/* Variables and functions */
 int DUMP_DEBUG_INFO ; 
 int MRB_DUMP_GENERAL_FAILURE ; 
 int MRB_DUMP_OK ; 
 int /*<<< orphan*/  create_lv_sym_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int**,int /*<<< orphan*/ *) ; 
 scalar_t__ debug_info_defined_p (int /*<<< orphan*/ *) ; 
 scalar_t__ get_debug_record_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_filename_table_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int**,int /*<<< orphan*/ *) ; 
 scalar_t__ get_irep_record_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_lv_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ lv_defined_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  write_footer (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  write_rite_binary_header (int /*<<< orphan*/ *,size_t,int*,int) ; 
 int write_section_debug (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int write_section_irep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,size_t*,int) ; 
 int write_section_lv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_irep(mrb_state *mrb, mrb_irep *irep, uint8_t flags, uint8_t **bin, size_t *bin_size)
{
  int result = MRB_DUMP_GENERAL_FAILURE;
  size_t malloc_size;
  size_t section_irep_size;
  size_t section_lineno_size = 0, section_lv_size = 0;
  uint8_t *cur = NULL;
  mrb_bool const debug_info_defined = debug_info_defined_p(irep), lv_defined = lv_defined_p(irep);
  mrb_sym *lv_syms = NULL; uint32_t lv_syms_len = 0;
  mrb_sym *filenames = NULL; uint16_t filenames_len = 0;

  if (mrb == NULL) {
    *bin = NULL;
    return MRB_DUMP_GENERAL_FAILURE;
  }

  section_irep_size = sizeof(struct rite_section_irep_header);
  section_irep_size += get_irep_record_size(mrb, irep);

  /* DEBUG section size */
  if (flags & DUMP_DEBUG_INFO) {
    if (debug_info_defined) {
      section_lineno_size += sizeof(struct rite_section_debug_header);
      /* filename table */
      filenames = (mrb_sym*)mrb_malloc(mrb, sizeof(mrb_sym) + 1);

      /* filename table size */
      section_lineno_size += sizeof(uint16_t);
      section_lineno_size += get_filename_table_size(mrb, irep, &filenames, &filenames_len);

      section_lineno_size += get_debug_record_size(mrb, irep);
    }
  }

  if (lv_defined) {
    section_lv_size += sizeof(struct rite_section_lv_header);
    create_lv_sym_table(mrb, irep, &lv_syms, &lv_syms_len);
    section_lv_size += get_lv_section_size(mrb, irep, lv_syms, lv_syms_len);
  }

  malloc_size = sizeof(struct rite_binary_header) +
                section_irep_size + section_lineno_size + section_lv_size +
                sizeof(struct rite_binary_footer);
  cur = *bin = (uint8_t*)mrb_malloc(mrb, malloc_size);
  cur += sizeof(struct rite_binary_header);

  result = write_section_irep(mrb, irep, cur, &section_irep_size, flags);
  if (result != MRB_DUMP_OK) {
    goto error_exit;
  }
  cur += section_irep_size;
  *bin_size = sizeof(struct rite_binary_header) +
              section_irep_size + section_lineno_size + section_lv_size +
              sizeof(struct rite_binary_footer);

  /* write DEBUG section */
  if (flags & DUMP_DEBUG_INFO) {
    if (debug_info_defined) {
      result = write_section_debug(mrb, irep, cur, filenames, filenames_len);
      if (result != MRB_DUMP_OK) {
        goto error_exit;
      }
    }
    cur += section_lineno_size;
  }

  if (lv_defined) {
    result = write_section_lv(mrb, irep, cur, lv_syms, lv_syms_len);
    if (result != MRB_DUMP_OK) {
      goto error_exit;
    }
    cur += section_lv_size;
  }

  write_footer(mrb, cur);
  write_rite_binary_header(mrb, *bin_size, *bin, flags);

error_exit:
  if (result != MRB_DUMP_OK) {
    mrb_free(mrb, *bin);
    *bin = NULL;
  }
  mrb_free(mrb, lv_syms);
  mrb_free(mrb, filenames);
  return result;
}