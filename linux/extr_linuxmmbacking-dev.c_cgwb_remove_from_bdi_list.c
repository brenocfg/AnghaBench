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
struct bdi_writeback {int /*<<< orphan*/  bdi_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgwb_remove_from_bdi_list(struct bdi_writeback *wb)
{
	list_del_rcu(&wb->bdi_node);
}