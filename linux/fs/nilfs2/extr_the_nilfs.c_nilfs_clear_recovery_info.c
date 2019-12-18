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
struct nilfs_recovery_info {int /*<<< orphan*/  ri_used_segments; } ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_dispose_segment_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_clear_recovery_info(struct nilfs_recovery_info *ri)
{
	nilfs_dispose_segment_list(&ri->ri_used_segments);
}