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
struct TYPE_2__ {scalar_t__ counter; scalar_t__ preempt_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  _schedule () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  disable_irq () ; 
 int /*<<< orphan*/  enable_irq () ; 

void timer_tick() {
  --current->counter;
  if (current->counter > 0 || current->preempt_count > 0) {
    return;
  }
  current->counter = 0;
  enable_irq();
  _schedule();
  disable_irq();
}