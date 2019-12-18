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
struct TYPE_3__ {int flags; } ;
struct batadv_tt_local_entry {TYPE_1__ common; } ;
struct TYPE_4__ {int flags; } ;
struct batadv_tt_global_entry {TYPE_2__ common; } ;

/* Variables and functions */
 int BATADV_TT_CLIENT_ISOLA ; 
 int BATADV_TT_CLIENT_WIFI ; 

__attribute__((used)) static bool
_batadv_is_ap_isolated(struct batadv_tt_local_entry *tt_local_entry,
		       struct batadv_tt_global_entry *tt_global_entry)
{
	if (tt_local_entry->common.flags & BATADV_TT_CLIENT_WIFI &&
	    tt_global_entry->common.flags & BATADV_TT_CLIENT_WIFI)
		return true;

	/* check if the two clients are marked as isolated */
	if (tt_local_entry->common.flags & BATADV_TT_CLIENT_ISOLA &&
	    tt_global_entry->common.flags & BATADV_TT_CLIENT_ISOLA)
		return true;

	return false;
}