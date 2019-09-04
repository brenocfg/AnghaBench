#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int current_state; int /*<<< orphan*/  current_step; } ;
typedef  TYPE_1__ DATA ;

/* Variables and functions */
 int N_STATES ; 
 int /*<<< orphan*/  write_io (TYPE_1__*) ; 

__attribute__((used)) static __attribute__((always_inline)) inline  void step_up(DATA *d)
{
  d->current_step++;
  d->current_state = (d->current_state + 1) % N_STATES;
  write_io(d);
}