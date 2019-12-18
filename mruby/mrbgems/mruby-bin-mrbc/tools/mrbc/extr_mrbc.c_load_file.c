#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mrbc_args {char** argv; size_t idx; char* prog; size_t argc; scalar_t__ verbose; } ;
struct TYPE_7__ {void* no_exec; void* dump_result; } ;
typedef  TYPE_1__ mrbc_context ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  void* mrb_bool ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  mrb_load_file_cxt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 scalar_t__ mrb_undef_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrbc_context_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* mrbc_context_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrbc_filename (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrbc_partial_hook (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  partial_hook ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 

__attribute__((used)) static mrb_value
load_file(mrb_state *mrb, struct mrbc_args *args)
{
  mrbc_context *c;
  mrb_value result;
  char *input = args->argv[args->idx];
  FILE *infile;
  mrb_bool need_close = FALSE;

  c = mrbc_context_new(mrb);
  if (args->verbose)
    c->dump_result = TRUE;
  c->no_exec = TRUE;
  if (input[0] == '-' && input[1] == '\0') {
    infile = stdin;
  }
  else {
    need_close = TRUE;
    if ((infile = fopen(input, "r")) == NULL) {
      fprintf(stderr, "%s: cannot open program file. (%s)\n", args->prog, input);
      return mrb_nil_value();
    }
  }
  mrbc_filename(mrb, c, input);
  args->idx++;
  if (args->idx < args->argc) {
    need_close = FALSE;
    mrbc_partial_hook(mrb, c, partial_hook, (void*)args);
  }

  result = mrb_load_file_cxt(mrb, infile, c);
  if (need_close) fclose(infile);
  mrbc_context_free(mrb, c);
  if (mrb_undef_p(result)) {
    return mrb_nil_value();
  }
  return result;
}