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
struct mdio_board_info {int dummy; } ;
struct mdio_board_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  board_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mdio_board_entry* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdio_board_list ; 
 int /*<<< orphan*/  mdio_board_lock ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mdio_board_info const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mdiobus_register_board_info(const struct mdio_board_info *info,
				unsigned int n)
{
	struct mdio_board_entry *be;
	unsigned int i;

	be = kcalloc(n, sizeof(*be), GFP_KERNEL);
	if (!be)
		return -ENOMEM;

	for (i = 0; i < n; i++, be++, info++) {
		memcpy(&be->board_info, info, sizeof(*info));
		mutex_lock(&mdio_board_lock);
		list_add_tail(&be->list, &mdio_board_list);
		mutex_unlock(&mdio_board_lock);
	}

	return 0;
}