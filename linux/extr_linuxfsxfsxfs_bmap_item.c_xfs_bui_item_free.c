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
struct xfs_bui_log_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,struct xfs_bui_log_item*) ; 
 int /*<<< orphan*/  xfs_bui_zone ; 

void
xfs_bui_item_free(
	struct xfs_bui_log_item	*buip)
{
	kmem_zone_free(xfs_bui_zone, buip);
}