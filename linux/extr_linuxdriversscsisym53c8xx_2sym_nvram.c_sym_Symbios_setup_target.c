#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sym_tcb {int usr_period; int usr_width; int /*<<< orphan*/  usrflags; scalar_t__ usrtags; } ;
struct TYPE_5__ {TYPE_1__* target; } ;
struct TYPE_4__ {int flags; int sync_period; int bus_width; } ;
typedef  TYPE_1__ Symbios_target ;
typedef  TYPE_2__ Symbios_nvram ;

/* Variables and functions */
 int SYMBIOS_DISCONNECT_ENABLE ; 
 int SYMBIOS_QUEUE_TAGS_ENABLED ; 
 int SYMBIOS_SCAN_AT_BOOT_TIME ; 
 int SYMBIOS_SCAN_LUNS ; 
 int /*<<< orphan*/  SYM_DISC_ENABLED ; 
 int /*<<< orphan*/  SYM_SCAN_BOOT_DISABLED ; 
 int /*<<< orphan*/  SYM_SCAN_LUNS_DISABLED ; 

__attribute__((used)) static void
sym_Symbios_setup_target(struct sym_tcb *tp, int target, Symbios_nvram *nvram)
{
	Symbios_target *tn = &nvram->target[target];

	if (!(tn->flags & SYMBIOS_QUEUE_TAGS_ENABLED))
		tp->usrtags = 0;
	if (!(tn->flags & SYMBIOS_DISCONNECT_ENABLE))
		tp->usrflags &= ~SYM_DISC_ENABLED;
	if (!(tn->flags & SYMBIOS_SCAN_AT_BOOT_TIME))
		tp->usrflags |= SYM_SCAN_BOOT_DISABLED;
	if (!(tn->flags & SYMBIOS_SCAN_LUNS))
		tp->usrflags |= SYM_SCAN_LUNS_DISABLED;
	tp->usr_period = (tn->sync_period + 3) / 4;
	tp->usr_width = (tn->bus_width == 0x8) ? 0 : 1;
}