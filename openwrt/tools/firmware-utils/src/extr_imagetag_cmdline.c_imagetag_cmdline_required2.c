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
struct gengetopt_args_info {int /*<<< orphan*/  entry_given; int /*<<< orphan*/  load_addr_given; int /*<<< orphan*/  chipid_given; int /*<<< orphan*/  boardid_given; int /*<<< orphan*/  output_given; int /*<<< orphan*/  rootfs_given; int /*<<< orphan*/  kernel_given; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_UNUSED (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

int
imagetag_cmdline_required2 (struct gengetopt_args_info *args_info, const char *prog_name, const char *additional_error)
{
  int error = 0;
  FIX_UNUSED (additional_error);

  /* checks for required options */
  if (! args_info->kernel_given)
    {
      fprintf (stderr, "%s: '--kernel' ('-i') option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->rootfs_given)
    {
      fprintf (stderr, "%s: '--rootfs' ('-f') option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->output_given)
    {
      fprintf (stderr, "%s: '--output' ('-o') option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->boardid_given)
    {
      fprintf (stderr, "%s: '--boardid' ('-b') option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->chipid_given)
    {
      fprintf (stderr, "%s: '--chipid' ('-c') option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->load_addr_given)
    {
      fprintf (stderr, "%s: '--load-addr' ('-l') option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->entry_given)
    {
      fprintf (stderr, "%s: '--entry' ('-e') option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  
  /* checks for dependences among options */

  return error;
}