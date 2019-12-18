#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int rlen; struct TYPE_7__** reps; } ;
typedef  TYPE_1__ mrb_irep ;
struct TYPE_8__ {int rcapa; TYPE_1__* irep; } ;
typedef  TYPE_2__ codegen_scope ;

/* Variables and functions */
 scalar_t__ codegen_realloc (TYPE_2__*,TYPE_1__**,int) ; 

__attribute__((used)) static void
scope_add_irep(codegen_scope *s, mrb_irep *irep)
{
  if (s->irep == NULL) {
    s->irep = irep;
    return;
  }
  if (s->irep->rlen == s->rcapa) {
    s->rcapa *= 2;
    s->irep->reps = (mrb_irep**)codegen_realloc(s, s->irep->reps, sizeof(mrb_irep*)*s->rcapa);
  }
  s->irep->reps[s->irep->rlen] = irep;
  s->irep->rlen++;
}