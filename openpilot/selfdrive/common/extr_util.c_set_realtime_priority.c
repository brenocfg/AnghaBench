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
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  SYS_gettid ; 
 int /*<<< orphan*/  memset (struct sched_param*,int /*<<< orphan*/ ,int) ; 
 int sched_setscheduler (long,int /*<<< orphan*/ ,struct sched_param*) ; 
 long syscall (int /*<<< orphan*/ ) ; 

int set_realtime_priority(int level) {
#ifdef __linux__

  long tid = syscall(SYS_gettid);

  // should match python using chrt
  struct sched_param sa;
  memset(&sa, 0, sizeof(sa));
  sa.sched_priority = level;
  return sched_setscheduler(tid, SCHED_FIFO, &sa);
#endif
}