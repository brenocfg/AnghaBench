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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {int /*<<< orphan*/  filename_sym; } ;
typedef  TYPE_1__ mrb_irep_debug_info_file ;
struct TYPE_6__ {int flen; TYPE_1__** files; } ;
typedef  TYPE_2__ mrb_irep_debug_info ;
struct TYPE_7__ {int rlen; struct TYPE_7__** reps; TYPE_2__* debug_info; } ;
typedef  TYPE_3__ mrb_irep ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int find_filename_index (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_assert (int*) ; 
 scalar_t__ mrb_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_sym_name_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static size_t
get_filename_table_size(mrb_state *mrb, mrb_irep *irep, mrb_sym **fp, uint16_t *lp)
{
  mrb_sym *filenames = *fp;
  size_t size = 0;
  mrb_irep_debug_info *di = irep->debug_info;
  int i;

  mrb_assert(lp);
  for (i = 0; i < di->flen; ++i) {
    mrb_irep_debug_info_file *file;
    mrb_int filename_len;

    file = di->files[i];
    if (find_filename_index(filenames, *lp, file->filename_sym) == -1) {
      /* register filename */
      *lp += 1;
      *fp = filenames = (mrb_sym *)mrb_realloc(mrb, filenames, sizeof(mrb_sym) * (*lp));
      filenames[*lp - 1] = file->filename_sym;

      /* filename */
      mrb_sym_name_len(mrb, file->filename_sym, &filename_len);
      size += sizeof(uint16_t) + (size_t)filename_len;
    }
  }
  for (i=0; i<irep->rlen; i++) {
    size += get_filename_table_size(mrb, irep->reps[i], fp, lp);
  }
  return size;
}