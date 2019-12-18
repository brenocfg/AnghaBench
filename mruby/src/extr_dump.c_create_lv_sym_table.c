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
typedef  int uint32_t ;
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {int nlocals; int rlen; struct TYPE_5__** reps; TYPE_1__* lv; } ;
typedef  TYPE_2__ mrb_irep ;
struct TYPE_4__ {scalar_t__ name; } ;

/* Variables and functions */
 int find_filename_index (scalar_t__*,int,scalar_t__ const) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mrb_realloc (int /*<<< orphan*/ *,scalar_t__*,int) ; 

__attribute__((used)) static void
create_lv_sym_table(mrb_state *mrb, const mrb_irep *irep, mrb_sym **syms, uint32_t *syms_len)
{
  int i;

  if (*syms == NULL) {
    *syms = (mrb_sym*)mrb_malloc(mrb, sizeof(mrb_sym) * 1);
  }

  for (i = 0; i + 1 < irep->nlocals; ++i) {
    mrb_sym const name = irep->lv[i].name;
    if (name == 0) continue;
    if (find_filename_index(*syms, *syms_len, name) != -1) continue;

    ++(*syms_len);
    *syms = (mrb_sym*)mrb_realloc(mrb, *syms, sizeof(mrb_sym) * (*syms_len));
    (*syms)[*syms_len - 1] = name;
  }

  for (i = 0; i < irep->rlen; ++i) {
    create_lv_sym_table(mrb, irep->reps[i], syms, syms_len);
  }
}