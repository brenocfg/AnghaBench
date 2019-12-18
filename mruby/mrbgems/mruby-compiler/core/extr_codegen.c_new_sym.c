#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mrb_sym ;
struct TYPE_5__ {int scapa; TYPE_3__* irep; } ;
typedef  TYPE_1__ codegen_scope ;
struct TYPE_6__ {int slen; scalar_t__* syms; } ;

/* Variables and functions */
 scalar_t__ codegen_realloc (TYPE_1__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  mrb_assert (TYPE_3__*) ; 

__attribute__((used)) static int
new_sym(codegen_scope *s, mrb_sym sym)
{
  int i, len;

  mrb_assert(s->irep);

  len = s->irep->slen;
  for (i=0; i<len; i++) {
    if (s->irep->syms[i] == sym) return i;
  }
  if (s->irep->slen >= s->scapa) {
    s->scapa *= 2;
    s->irep->syms = (mrb_sym*)codegen_realloc(s, s->irep->syms, sizeof(mrb_sym)*s->scapa);
  }
  s->irep->syms[s->irep->slen] = sym;
  return s->irep->slen++;
}