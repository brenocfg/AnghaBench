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
struct aa_loaddata {int /*<<< orphan*/ ** dents; } ;

/* Variables and functions */
 int AAFS_LOADDATA_NDENTS ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aafs_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_rawdata_dents(struct aa_loaddata *rawdata)
{
	int i;

	for (i = 0; i < AAFS_LOADDATA_NDENTS; i++) {
		if (!IS_ERR_OR_NULL(rawdata->dents[i])) {
			/* no refcounts on i_private */
			aafs_remove(rawdata->dents[i]);
			rawdata->dents[i] = NULL;
		}
	}
}