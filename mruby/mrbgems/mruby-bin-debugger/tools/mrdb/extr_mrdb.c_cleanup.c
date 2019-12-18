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
struct _args {int /*<<< orphan*/  argv; int /*<<< orphan*/  srcpath; scalar_t__ rfp; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  mrb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrdb_state_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cleanup(mrb_state *mrb, struct _args *args)
{
  if (args->rfp)
    fclose(args->rfp);
  if (args->srcpath)
    mrb_free(mrb, args->srcpath);
  if (args->argv)
    mrb_free(mrb, args->argv);
  mrdb_state_free(mrb);
  mrb_close(mrb);
}