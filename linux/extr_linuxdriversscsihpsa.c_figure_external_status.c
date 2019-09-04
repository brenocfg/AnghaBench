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
struct ctlr_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int  figure_external_status(struct ctlr_info *h, int raid_ctlr_position,
	int i, int nphysicals, int nlocal_logicals)
{
	/* In report logicals, local logicals are listed first,
	* then any externals.
	*/
	int logicals_start = nphysicals + (raid_ctlr_position == 0);

	if (i == raid_ctlr_position)
		return 0;

	if (i < logicals_start)
		return 0;

	/* i is in logicals range, but still within local logicals */
	if ((i - nphysicals - (raid_ctlr_position == 0)) < nlocal_logicals)
		return 0;

	return 1; /* it's an external lun */
}