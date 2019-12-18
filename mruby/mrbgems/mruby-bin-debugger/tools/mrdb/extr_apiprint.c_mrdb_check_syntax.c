#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lineno; void* capture_errors; void* no_exec; } ;
typedef  TYPE_1__ mrbc_context ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_9__ {int /*<<< orphan*/  prvline; scalar_t__ prvfile; } ;
typedef  TYPE_2__ mrb_debug_context ;

/* Variables and functions */
 void* TRUE ; 
 int /*<<< orphan*/  mrb_load_nstring_cxt (int /*<<< orphan*/ *,char const*,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  mrbc_context_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* mrbc_context_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrbc_filename (int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 

__attribute__((used)) static void
mrdb_check_syntax(mrb_state *mrb, mrb_debug_context *dbg, const char *expr, size_t len)
{
  mrbc_context *c;

  c = mrbc_context_new(mrb);
  c->no_exec = TRUE;
  c->capture_errors = TRUE;
  mrbc_filename(mrb, c, (const char*)dbg->prvfile);
  c->lineno = dbg->prvline;

  /* Load program */
  mrb_load_nstring_cxt(mrb, expr, len, c);

  mrbc_context_free(mrb, c);
}