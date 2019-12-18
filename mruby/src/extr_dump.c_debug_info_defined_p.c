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
struct TYPE_3__ {int rlen; struct TYPE_3__** reps; int /*<<< orphan*/  debug_info; } ;
typedef  TYPE_1__ mrb_irep ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static mrb_bool
debug_info_defined_p(mrb_irep *irep)
{
  int i;

  if (!irep->debug_info) return FALSE;
  for (i=0; i<irep->rlen; i++) {
    if (!debug_info_defined_p(irep->reps[i])) return FALSE;
  }
  return TRUE;
}