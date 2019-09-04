#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ofdpa_group_tbl_entry {struct ofdpa_group_tbl_entry* group_ids; int /*<<< orphan*/  group_id; } ;

/* Variables and functions */
 int ROCKER_GROUP_TYPE_GET (int /*<<< orphan*/ ) ; 
#define  ROCKER_OF_DPA_GROUP_TYPE_L2_FLOOD 129 
#define  ROCKER_OF_DPA_GROUP_TYPE_L2_MCAST 128 
 int /*<<< orphan*/  kfree (struct ofdpa_group_tbl_entry*) ; 

__attribute__((used)) static void ofdpa_group_tbl_entry_free(struct ofdpa_group_tbl_entry *entry)
{
	switch (ROCKER_GROUP_TYPE_GET(entry->group_id)) {
	case ROCKER_OF_DPA_GROUP_TYPE_L2_FLOOD:
	case ROCKER_OF_DPA_GROUP_TYPE_L2_MCAST:
		kfree(entry->group_ids);
		break;
	default:
		break;
	}
	kfree(entry);
}