#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ active; int /*<<< orphan*/  exist; scalar_t__ new; } ;
struct pvc_device {TYPE_1__ state; TYPE_3__* ether; TYPE_2__* main; int /*<<< orphan*/  dlci; int /*<<< orphan*/  frad; } ;
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static inline void fr_log_dlci_active(struct pvc_device *pvc)
{
	netdev_info(pvc->frad, "DLCI %d [%s%s%s]%s %s\n",
		    pvc->dlci,
		    pvc->main ? pvc->main->name : "",
		    pvc->main && pvc->ether ? " " : "",
		    pvc->ether ? pvc->ether->name : "",
		    pvc->state.new ? " new" : "",
		    !pvc->state.exist ? "deleted" :
		    pvc->state.active ? "active" : "inactive");
}