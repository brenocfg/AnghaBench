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
struct TYPE_2__ {int /*<<< orphan*/  target; } ;
struct sljit_jump {TYPE_1__ u; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  sljit_uw ;

/* Variables and functions */
 int /*<<< orphan*/  JUMP_ADDR ; 
 int /*<<< orphan*/  JUMP_LABEL ; 
 scalar_t__ SLJIT_LIKELY (int) ; 

void sljit_set_target(struct sljit_jump *jump, sljit_uw target)
{
	if (SLJIT_LIKELY(!!jump)) {
		jump->flags &= ~JUMP_LABEL;
		jump->flags |= JUMP_ADDR;
		jump->u.target = target;
	}
}