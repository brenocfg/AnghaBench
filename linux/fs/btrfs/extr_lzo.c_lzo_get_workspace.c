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
struct list_head {int dummy; } ;

/* Variables and functions */
 struct list_head* btrfs_get_workspace (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  wsm ; 

__attribute__((used)) static struct list_head *lzo_get_workspace(unsigned int level)
{
	return btrfs_get_workspace(&wsm, level);
}