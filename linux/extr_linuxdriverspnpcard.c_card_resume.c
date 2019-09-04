#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pnp_dev {struct pnp_card_link* card_link; } ;
struct TYPE_4__ {scalar_t__ event; } ;
struct pnp_card_link {TYPE_1__* driver; TYPE_2__ pm_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* resume ) (struct pnp_card_link*) ;} ;

/* Variables and functions */
 TYPE_2__ PMSG_ON ; 
 scalar_t__ PM_EVENT_ON ; 
 int /*<<< orphan*/  stub1 (struct pnp_card_link*) ; 

__attribute__((used)) static int card_resume(struct pnp_dev *dev)
{
	struct pnp_card_link *link = dev->card_link;

	if (link->pm_state.event == PM_EVENT_ON)
		return 0;
	link->pm_state = PMSG_ON;
	link->driver->resume(link);
	return 0;
}