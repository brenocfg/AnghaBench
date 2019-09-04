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
typedef  scalar_t__ u64 ;
struct tb_hotplug_event {int /*<<< orphan*/  work; int /*<<< orphan*/  unplug; int /*<<< orphan*/  port; scalar_t__ route; struct tb* tb; } ;
struct tb {int /*<<< orphan*/  wq; int /*<<< orphan*/  ctl; } ;
struct cfg_event_pkg {int /*<<< orphan*/  unplug; int /*<<< orphan*/  port; int /*<<< orphan*/  header; } ;
typedef  enum tb_cfg_pkg_type { ____Placeholder_tb_cfg_pkg_type } tb_cfg_pkg_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_CFG_ERROR_ACK_PLUG_EVENT ; 
 int TB_CFG_PKG_EVENT ; 
 struct tb_hotplug_event* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tb_cfg_error (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tb_cfg_get_route (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_handle_hotplug ; 
 int /*<<< orphan*/  tb_warn (struct tb*,char*,int,...) ; 

__attribute__((used)) static void tb_handle_event(struct tb *tb, enum tb_cfg_pkg_type type,
			    const void *buf, size_t size)
{
	const struct cfg_event_pkg *pkg = buf;
	struct tb_hotplug_event *ev;
	u64 route;

	if (type != TB_CFG_PKG_EVENT) {
		tb_warn(tb, "unexpected event %#x, ignoring\n", type);
		return;
	}

	route = tb_cfg_get_route(&pkg->header);

	if (tb_cfg_error(tb->ctl, route, pkg->port,
			 TB_CFG_ERROR_ACK_PLUG_EVENT)) {
		tb_warn(tb, "could not ack plug event on %llx:%x\n", route,
			pkg->port);
	}

	ev = kmalloc(sizeof(*ev), GFP_KERNEL);
	if (!ev)
		return;
	INIT_WORK(&ev->work, tb_handle_hotplug);
	ev->tb = tb;
	ev->route = route;
	ev->port = pkg->port;
	ev->unplug = pkg->unplug;
	queue_work(tb->wq, &ev->work);
}