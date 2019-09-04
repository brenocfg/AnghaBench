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
struct channel_path {int /*<<< orphan*/  desc_fmt3; int /*<<< orphan*/  chpid; int /*<<< orphan*/  desc_fmt1; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int chsc_determine_fmt0_channel_path_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chsc_determine_fmt1_channel_path_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chsc_determine_fmt3_channel_path_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chsc_get_channel_measurement_chars (struct channel_path*) ; 

int chp_update_desc(struct channel_path *chp)
{
	int rc;

	rc = chsc_determine_fmt0_channel_path_desc(chp->chpid, &chp->desc);
	if (rc)
		return rc;

	/*
	 * Fetching the following data is optional. Not all machines or
	 * hypervisors implement the required chsc commands.
	 */
	chsc_determine_fmt1_channel_path_desc(chp->chpid, &chp->desc_fmt1);
	chsc_determine_fmt3_channel_path_desc(chp->chpid, &chp->desc_fmt3);
	chsc_get_channel_measurement_chars(chp);

	return 0;
}