#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ fault_handling; int load_threads; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_HANDLER ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/ * _mem ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_thread ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int libkdump_cleanup() {
  int j;
  if (config.fault_handling == SIGNAL_HANDLER) {
    signal(SIGSEGV, SIG_DFL);
  }

  for (j = 0; j < config.load_threads; j++) {
    pthread_cancel(load_thread[j]);
  }
  free(load_thread);
  free(_mem);
  debug(SUCCESS, "Everything is cleaned up, good bye!\n");
  return 0;
}