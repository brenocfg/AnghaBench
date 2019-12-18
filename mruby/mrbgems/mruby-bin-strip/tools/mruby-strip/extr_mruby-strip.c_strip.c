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
struct strip_args {int argc_start; int argc; char** argv; scalar_t__ lvar; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int MRB_DUMP_OK ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int mrb_dump_irep_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_irep_decref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_irep_remove_lv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mrb_read_irep_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
strip(mrb_state *mrb, struct strip_args *args)
{
  int i;

  for (i = args->argc_start; i < args->argc; ++i) {
    char *filename;
    FILE *rfile;
    mrb_irep *irep;
    FILE *wfile;
    int dump_result;

    filename = args->argv[i];
    rfile = fopen(filename, "rb");
    if (rfile == NULL) {
      fprintf(stderr, "can't open file for reading %s\n", filename);
      return EXIT_FAILURE;
    }

    irep = mrb_read_irep_file(mrb, rfile);
    fclose(rfile);
    if (irep == NULL) {
      fprintf(stderr, "can't read irep file %s\n", filename);
      return EXIT_FAILURE;
    }

    /* clear lv if --lvar is enabled */
    if (args->lvar) {
      mrb_irep_remove_lv(mrb, irep);
    }

    wfile = fopen(filename, "wb");
    if (wfile == NULL) {
      fprintf(stderr, "can't open file for writing %s\n", filename);
      mrb_irep_decref(mrb, irep);
      return EXIT_FAILURE;
    }

    /* debug flag must always be false */
    dump_result = mrb_dump_irep_binary(mrb, irep, FALSE, wfile);

    fclose(wfile);
    mrb_irep_decref(mrb, irep);

    if (dump_result != MRB_DUMP_OK) {
      fprintf(stderr, "error occurred during dumping %s\n", filename);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}