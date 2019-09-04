#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ q_len; int* q_buf; int core_stat; } ;
typedef  TYPE_1__ stlink_t ;

/* Variables and functions */
#define  STLINK_CORE_HALTED 129 
#define  STLINK_CORE_RUNNING 128 
 int STLINK_CORE_STAT_UNKNOWN ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void stlink_core_stat(stlink_t *sl) {
  if (sl->q_len <= 0) return;

  switch (sl->q_buf[0]) {
    case STLINK_CORE_RUNNING:
      sl->core_stat = STLINK_CORE_RUNNING;
      return;
    case STLINK_CORE_HALTED:
      sl->core_stat = STLINK_CORE_HALTED;
      return;
    default:
      sl->core_stat = STLINK_CORE_STAT_UNKNOWN;
      fprintf(stderr, "  core status: unknown\n");
  }
}