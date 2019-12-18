#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct mrb_irep {size_t rlen; struct mrb_irep** reps; TYPE_1__* debug_info; } ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {int /*<<< orphan*/  filename_sym; } ;
typedef  TYPE_2__ mrb_irep_debug_info_file ;
struct TYPE_4__ {size_t flen; TYPE_2__** files; } ;

/* Variables and functions */
 size_t MRB_DEBUG_BP_FILE_OK ; 
 size_t MRB_DEBUG_BP_LINENO_OK ; 
 size_t check_lineno (TYPE_2__*,size_t) ; 
 char* mrb_sym_name_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static uint16_t
check_file_lineno(mrb_state *mrb, struct mrb_irep *irep, const char *file, uint16_t lineno)
{
  mrb_irep_debug_info_file *info_file;
  uint16_t result = 0;
  uint16_t f_idx;
  uint16_t fix_lineno;
  uint16_t i;

  for (f_idx = 0; f_idx < irep->debug_info->flen; ++f_idx) {
    const char *filename;
    info_file = irep->debug_info->files[f_idx];
    filename = mrb_sym_name_len(mrb, info_file->filename_sym, NULL);
    if (!strcmp(filename, file)) {
      result = MRB_DEBUG_BP_FILE_OK;

      fix_lineno = check_lineno(info_file, lineno);
      if (fix_lineno != 0) {
        return result | MRB_DEBUG_BP_LINENO_OK;
      }
    }
    for (i=0; i < irep->rlen; ++i) {
      result  |= check_file_lineno(mrb, irep->reps[i], file, lineno);
      if (result == (MRB_DEBUG_BP_FILE_OK | MRB_DEBUG_BP_LINENO_OK)) {
        return result;
      }
    }
  }
  return result;
}