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

/* Variables and functions */
 scalar_t__ EMFILE ; 
 scalar_t__ ENFILE ; 
 scalar_t__ errno ; 
 int mrb_cloexec_pipe (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mrb_garbage_collect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mrb_pipe(mrb_state *mrb, int pipes[2])
{
  int ret;
  ret = mrb_cloexec_pipe(mrb, pipes);
  if (ret == -1) {
    if (errno == EMFILE || errno == ENFILE) {
      mrb_garbage_collect(mrb);
      ret = mrb_cloexec_pipe(mrb, pipes);
    }
  }
  return ret;
}