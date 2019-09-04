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
struct fsg_common {int /*<<< orphan*/ ** luns; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsg_common_remove_lun (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _fsg_common_remove_luns(struct fsg_common *common, int n)
{
	int i;

	for (i = 0; i < n; ++i)
		if (common->luns[i]) {
			fsg_common_remove_lun(common->luns[i]);
			common->luns[i] = NULL;
		}
}