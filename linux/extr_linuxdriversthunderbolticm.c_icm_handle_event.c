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
struct tb {int /*<<< orphan*/  wq; } ;
struct icm_notification {int /*<<< orphan*/  work; struct tb* tb; int /*<<< orphan*/  pkg; } ;
typedef  enum tb_cfg_pkg_type { ____Placeholder_tb_cfg_pkg_type } tb_cfg_pkg_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icm_handle_notification ; 
 struct icm_notification* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icm_handle_event(struct tb *tb, enum tb_cfg_pkg_type type,
			     const void *buf, size_t size)
{
	struct icm_notification *n;

	n = kmalloc(sizeof(*n), GFP_KERNEL);
	if (!n)
		return;

	INIT_WORK(&n->work, icm_handle_notification);
	n->pkg = kmemdup(buf, size, GFP_KERNEL);
	n->tb = tb;

	queue_work(tb->wq, &n->work);
}