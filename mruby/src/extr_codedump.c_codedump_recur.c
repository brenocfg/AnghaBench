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
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_4__ {int rlen; struct TYPE_4__** reps; } ;
typedef  TYPE_1__ mrb_irep ;

/* Variables and functions */
 int /*<<< orphan*/  codedump (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
codedump_recur(mrb_state *mrb, mrb_irep *irep)
{
  int i;

  codedump(mrb, irep);
  for (i=0; i<irep->rlen; i++) {
    codedump_recur(mrb, irep->reps[i]);
  }
}