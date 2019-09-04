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
struct skl_lib_info {int /*<<< orphan*/ * fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

void skl_release_library(struct skl_lib_info *linfo, int lib_count)
{
	int i;

	/* library indices start from 1 to N. 0 represents base FW */
	for (i = 1; i < lib_count; i++) {
		if (linfo[i].fw) {
			release_firmware(linfo[i].fw);
			linfo[i].fw = NULL;
		}
	}
}