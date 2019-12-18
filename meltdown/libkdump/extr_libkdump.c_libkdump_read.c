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
typedef  int /*<<< orphan*/  res_stat ;
struct TYPE_2__ {int measurements; scalar_t__ fault_handling; char accept_after; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 scalar_t__ TSX ; 
 TYPE_1__ config ; 
 scalar_t__ dbg ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int,char) ; 
 int libkdump_read_signal_handler () ; 
 int libkdump_read_tsx () ; 
 size_t phys ; 
 int /*<<< orphan*/  sched_yield () ; 

int __attribute__((optimize("-O0"))) libkdump_read(size_t addr) {
  phys = addr;

  char res_stat[256];
  int i, j, r;
  for (i = 0; i < 256; i++)
    res_stat[i] = 0;

  sched_yield();

  for (i = 0; i < config.measurements; i++) {
    if (config.fault_handling == TSX) {
      r = libkdump_read_tsx();
    } else {
      r = libkdump_read_signal_handler();
    }
    res_stat[r]++;
  }
  int max_v = 0, max_i = 0;

  if (dbg) {
    for (i = 0; i < sizeof(res_stat); i++) {
      if (res_stat[i] == 0)
        continue;
      debug(INFO, "res_stat[%x] = %d\n",
            i, res_stat[i]);
    }
  }

  for (i = 1; i < 256; i++) {
    if (res_stat[i] > max_v && res_stat[i] >= config.accept_after) {
      max_v = res_stat[i];
      max_i = i;
    }
  }
  return max_i;
}