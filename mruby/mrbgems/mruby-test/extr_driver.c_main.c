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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int eval_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_test_driver (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_load_irep (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mrb_open () ; 
 int /*<<< orphan*/  mrbgemtest_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrbtest_assert_irep ; 
 int /*<<< orphan*/  print_hint () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char **argv)
{
  mrb_state *mrb;
  int ret;
  mrb_bool verbose = FALSE;

  print_hint();

  /* new interpreter instance */
  mrb = mrb_open();
  if (mrb == NULL) {
    fprintf(stderr, "Invalid mrb_state, exiting test driver");
    return EXIT_FAILURE;
  }

  if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'v') {
    printf("verbose mode: enable\n\n");
    verbose = TRUE;
  }

  mrb_init_test_driver(mrb, verbose);
  mrb_load_irep(mrb, mrbtest_assert_irep);
  mrbgemtest_init(mrb);
  ret = eval_test(mrb);
  mrb_close(mrb);

  return ret;
}