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
struct fsg_common {int /*<<< orphan*/  luns; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fsg_common_remove_luns (struct fsg_common*,int /*<<< orphan*/ ) ; 

void fsg_common_remove_luns(struct fsg_common *common)
{
	_fsg_common_remove_luns(common, ARRAY_SIZE(common->luns));
}