#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rlen; struct TYPE_5__** reps; } ;
typedef  TYPE_1__ mrb_irep ;

/* Variables and functions */

__attribute__((used)) static mrb_irep*
search_irep(mrb_irep *top, int bnest, int lev, mrb_irep *bottom)
{
  int i;

  for (i=0; i<top->rlen; i++) {
    mrb_irep* tmp = top->reps[i];

    if (tmp == bottom) return top;
    tmp = search_irep(tmp, bnest-1, lev, bottom);
    if (tmp) {
      if (bnest == lev) return top;
      return tmp;
    }
  }
  return NULL;
}