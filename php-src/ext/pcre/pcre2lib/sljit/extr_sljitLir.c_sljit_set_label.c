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
struct sljit_label {int dummy; } ;
struct TYPE_2__ {struct sljit_label* label; } ;
struct sljit_jump {TYPE_1__ u; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  JUMP_ADDR ; 
 int /*<<< orphan*/  JUMP_LABEL ; 
 scalar_t__ SLJIT_LIKELY (int) ; 

void sljit_set_label(struct sljit_jump *jump, struct sljit_label* label)
{
	if (SLJIT_LIKELY(!!jump) && SLJIT_LIKELY(!!label)) {
		jump->flags &= ~JUMP_ADDR;
		jump->flags |= JUMP_LABEL;
		jump->u.label = label;
	}
}