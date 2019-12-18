#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mrb_value ;
typedef  TYPE_1__* mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_11__ {int ilen; int plen; int slen; int rlen; int nlocals; int /*<<< orphan*/  nregs; int /*<<< orphan*/  debug_info; struct TYPE_11__** reps; struct TYPE_11__** syms; struct TYPE_11__** pool; int /*<<< orphan*/ * iseq; scalar_t__ flags; } ;
typedef  TYPE_1__ mrb_irep ;
typedef  int /*<<< orphan*/  mrb_code ;
struct TYPE_12__ {int nlocals; int pc; int /*<<< orphan*/  mpool; int /*<<< orphan*/  ai; int /*<<< orphan*/  nregs; int /*<<< orphan*/  lines; int /*<<< orphan*/ * mrb; int /*<<< orphan*/  debug_start_pos; TYPE_1__* irep; int /*<<< orphan*/  filename_index; int /*<<< orphan*/  parser; scalar_t__ filename_sym; TYPE_1__** iseq; } ;
typedef  TYPE_4__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  codegen_error (TYPE_4__*,char*) ; 
 scalar_t__ codegen_realloc (TYPE_4__*,TYPE_1__**,int) ; 
 int /*<<< orphan*/  mrb_debug_info_append_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* mrb_parser_get_filename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_pool_close (int /*<<< orphan*/ ) ; 
 char* mrb_sym_name_len (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scope_finish(codegen_scope *s)
{
  mrb_state *mrb = s->mrb;
  mrb_irep *irep = s->irep;

  if (s->nlocals >= 0x3ff) {
    codegen_error(s, "too many local variables");
  }
  irep->flags = 0;
  if (s->iseq) {
    irep->iseq = (mrb_code *)codegen_realloc(s, s->iseq, sizeof(mrb_code)*s->pc);
    irep->ilen = s->pc;
  }
  irep->pool = (mrb_value*)codegen_realloc(s, irep->pool, sizeof(mrb_value)*irep->plen);
  irep->syms = (mrb_sym*)codegen_realloc(s, irep->syms, sizeof(mrb_sym)*irep->slen);
  irep->reps = (mrb_irep**)codegen_realloc(s, irep->reps, sizeof(mrb_irep*)*irep->rlen);
  if (s->filename_sym) {
    mrb_sym fname = mrb_parser_get_filename(s->parser, s->filename_index);
    const char *filename = mrb_sym_name_len(s->mrb, fname, NULL);

    mrb_debug_info_append_file(s->mrb, s->irep->debug_info,
                               filename, s->lines, s->debug_start_pos, s->pc);
  }
  mrb_free(s->mrb, s->lines);

  irep->nlocals = s->nlocals;
  irep->nregs = s->nregs;

  mrb_gc_arena_restore(mrb, s->ai);
  mrb_pool_close(s->mpool);
}