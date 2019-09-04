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
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nilfs_recovery_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nilfs_init_recovery_info(struct nilfs_recovery_info *ri)
{
	memset(ri, 0, sizeof(*ri));
	INIT_LIST_HEAD(&ri->ri_used_segments);
}