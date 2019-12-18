#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mrb_parser_state {int dummy; } ;
struct RProc {int dummy; } ;
typedef  int /*<<< orphan*/  mrbc_context ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_close (int /*<<< orphan*/ *) ; 
 struct RProc* mrb_generate_code (int /*<<< orphan*/ *,struct mrb_parser_state*) ; 
 struct mrb_parser_state* mrb_parse_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_parser_free (struct mrb_parser_state*) ; 
 int /*<<< orphan*/  mrb_top_self (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_vm_run (int /*<<< orphan*/ *,struct RProc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void decl_lv_underscore(mrb_state *mrb, mrbc_context *cxt)
{
  struct RProc *proc;
  struct mrb_parser_state *parser;

  parser = mrb_parse_string(mrb, "_=nil", cxt);
  if (parser == NULL) {
    fputs("create parser state error\n", stderr);
    mrb_close(mrb);
    exit(EXIT_FAILURE);
  }

  proc = mrb_generate_code(mrb, parser);
  mrb_vm_run(mrb, proc, mrb_top_self(mrb), 0);

  mrb_parser_free(parser);
}