#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int lineno; int /*<<< orphan*/  jmp; scalar_t__ filename_sym; int /*<<< orphan*/  mrb; int /*<<< orphan*/  mpool; int /*<<< orphan*/  lines; int /*<<< orphan*/  iseq; struct TYPE_3__* prev; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_THROW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_pool_close (int /*<<< orphan*/ ) ; 
 char* mrb_sym_name_len (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
codegen_error(codegen_scope *s, const char *message)
{
  if (!s) return;
  while (s->prev) {
    codegen_scope *tmp = s->prev;
    mrb_free(s->mrb, s->iseq);
    mrb_free(s->mrb, s->lines);
    mrb_pool_close(s->mpool);
    s = tmp;
  }
#ifndef MRB_DISABLE_STDIO
  if (s->filename_sym && s->lineno) {
    const char *filename = mrb_sym_name_len(s->mrb, s->filename_sym, NULL);
    fprintf(stderr, "codegen error:%s:%d: %s\n", filename, s->lineno, message);
  }
  else {
    fprintf(stderr, "codegen error: %s\n", message);
  }
#endif
  MRB_THROW(&s->jmp);
}