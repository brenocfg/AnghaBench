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
struct vscsibk_info {TYPE_1__* dev; } ;
struct ids_tuple {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  XenbusStateClosed ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  scsiback_del_translation_entry (struct vscsibk_info*,struct ids_tuple*) ; 
 scalar_t__ xenbus_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsiback_do_del_lun(struct vscsibk_info *info, const char *state,
				struct ids_tuple *vir)
{
	if (!scsiback_del_translation_entry(info, vir)) {
		if (xenbus_printf(XBT_NIL, info->dev->nodename, state,
				  "%d", XenbusStateClosed))
			pr_err("xenbus_printf error %s\n", state);
	}
}