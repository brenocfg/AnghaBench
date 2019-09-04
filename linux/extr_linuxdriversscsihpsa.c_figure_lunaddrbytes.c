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
typedef  int /*<<< orphan*/  u8 ;
struct ctlr_info {int dummy; } ;
struct ReportLUNdata {int /*<<< orphan*/ ** LUN; } ;
struct ReportExtendedLUNdata {TYPE_1__* LUN; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lunid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/ * RAID_CTLR_LUNID ; 

__attribute__((used)) static u8 *figure_lunaddrbytes(struct ctlr_info *h, int raid_ctlr_position,
	int i, int nphysicals, int nlogicals,
	struct ReportExtendedLUNdata *physdev_list,
	struct ReportLUNdata *logdev_list)
{
	/* Helper function, figure out where the LUN ID info is coming from
	 * given index i, lists of physical and logical devices, where in
	 * the list the raid controller is supposed to appear (first or last)
	 */

	int logicals_start = nphysicals + (raid_ctlr_position == 0);
	int last_device = nphysicals + nlogicals + (raid_ctlr_position == 0);

	if (i == raid_ctlr_position)
		return RAID_CTLR_LUNID;

	if (i < logicals_start)
		return &physdev_list->LUN[i -
				(raid_ctlr_position == 0)].lunid[0];

	if (i < last_device)
		return &logdev_list->LUN[i - nphysicals -
			(raid_ctlr_position == 0)][0];
	BUG();
	return NULL;
}