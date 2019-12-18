#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct _args {char* cmdline; int argc; char** argv; int libc; char** libv; scalar_t__ check_syntax; int /*<<< orphan*/ * rfp; scalar_t__ mrbfile; scalar_t__ verbose; int /*<<< orphan*/  debug; } ;
struct TYPE_28__ {void* no_exec; void* dump_result; } ;
typedef  TYPE_1__ mrbc_context ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
struct TYPE_29__ {scalar_t__ exc; } ;
typedef  TYPE_2__ mrb_state ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 void* TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  cleanup (TYPE_2__*,struct _args*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mrb_ary_push (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_bool_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_global_const (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (TYPE_2__*,int) ; 
 int mrb_gc_arena_save (TYPE_2__*) ; 
 int /*<<< orphan*/  mrb_gv_set (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  mrb_load_file_cxt (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_load_irep_file_cxt (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_load_string_cxt (TYPE_2__*,char*,TYPE_1__*) ; 
 TYPE_2__* mrb_open () ; 
 int /*<<< orphan*/  mrb_print_error (TYPE_2__*) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  mrb_str_new_lit (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  mrb_undef_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_utf8_free (char*) ; 
 char* mrb_utf8_from_locale (char*,int) ; 
 int /*<<< orphan*/  mrbc_context_free (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* mrbc_context_new (TYPE_2__*) ; 
 int /*<<< orphan*/  mrbc_filename (TYPE_2__*,TYPE_1__*,char const*) ; 
 int parse_args (TYPE_2__*,int,char**,struct _args*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char **argv)
{
  mrb_state *mrb = mrb_open();
  int n = -1;
  int i;
  struct _args args;
  mrb_value ARGV;
  mrbc_context *c;
  mrb_value v;
  mrb_sym zero_sym;

  if (mrb == NULL) {
    fprintf(stderr, "%s: Invalid mrb_state, exiting mruby\n", *argv);
    return EXIT_FAILURE;
  }

  n = parse_args(mrb, argc, argv, &args);
  if (n == EXIT_FAILURE || (args.cmdline == NULL && args.rfp == NULL)) {
    cleanup(mrb, &args);
    return n;
  }
  else {
    int ai = mrb_gc_arena_save(mrb);
    ARGV = mrb_ary_new_capa(mrb, args.argc);
    for (i = 0; i < args.argc; i++) {
      char* utf8 = mrb_utf8_from_locale(args.argv[i], -1);
      if (utf8) {
        mrb_ary_push(mrb, ARGV, mrb_str_new_cstr(mrb, utf8));
        mrb_utf8_free(utf8);
      }
    }
    mrb_define_global_const(mrb, "ARGV", ARGV);
    mrb_gv_set(mrb, mrb_intern_lit(mrb, "$DEBUG"), mrb_bool_value(args.debug));

    c = mrbc_context_new(mrb);
    if (args.verbose)
      c->dump_result = TRUE;
    if (args.check_syntax)
      c->no_exec = TRUE;

    /* Set $0 */
    zero_sym = mrb_intern_lit(mrb, "$0");
    if (args.rfp) {
      const char *cmdline;
      cmdline = args.cmdline ? args.cmdline : "-";
      mrbc_filename(mrb, c, cmdline);
      mrb_gv_set(mrb, zero_sym, mrb_str_new_cstr(mrb, cmdline));
    }
    else {
      mrbc_filename(mrb, c, "-e");
      mrb_gv_set(mrb, zero_sym, mrb_str_new_lit(mrb, "-e"));
    }

    /* Load libraries */
    for (i = 0; i < args.libc; i++) {
      FILE *lfp = fopen(args.libv[i], args.mrbfile ? "rb" : "r");
      if (lfp == NULL) {
        fprintf(stderr, "%s: Cannot open library file: %s\n", *argv, args.libv[i]);
        mrbc_context_free(mrb, c);
        cleanup(mrb, &args);
        return EXIT_FAILURE;
      }
      if (args.mrbfile) {
        v = mrb_load_irep_file_cxt(mrb, lfp, c);
      }
      else {
        v = mrb_load_file_cxt(mrb, lfp, c);
      }
      fclose(lfp);
    }

    /* Load program */
    if (args.mrbfile) {
      v = mrb_load_irep_file_cxt(mrb, args.rfp, c);
    }
    else if (args.rfp) {
      v = mrb_load_file_cxt(mrb, args.rfp, c);
    }
    else {
      char* utf8 = mrb_utf8_from_locale(args.cmdline, -1);
      if (!utf8) abort();
      v = mrb_load_string_cxt(mrb, utf8, c);
      mrb_utf8_free(utf8);
    }

    mrb_gc_arena_restore(mrb, ai);
    mrbc_context_free(mrb, c);
    if (mrb->exc) {
      if (!mrb_undef_p(v)) {
        mrb_print_error(mrb);
      }
      n = EXIT_FAILURE;
    }
    else if (args.check_syntax) {
      puts("Syntax OK");
    }
  }
  cleanup(mrb, &args);

  return n;
}