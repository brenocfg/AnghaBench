#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct netlink_ext_ack* extack; } ;
struct fib_entry_notifier_info {int dst_len; TYPE_1__ info; int /*<<< orphan*/  tb_id; int /*<<< orphan*/  type; int /*<<< orphan*/  tos; int /*<<< orphan*/  fi; int /*<<< orphan*/  dst; } ;
struct fib_alias {int /*<<< orphan*/  tb_id; int /*<<< orphan*/  fa_type; int /*<<< orphan*/  fa_tos; int /*<<< orphan*/  fa_info; } ;
typedef  enum fib_event_type { ____Placeholder_fib_event_type } fib_event_type ;

/* Variables and functions */
 int call_fib4_notifiers (struct net*,int,TYPE_1__*) ; 

__attribute__((used)) static int call_fib_entry_notifiers(struct net *net,
				    enum fib_event_type event_type, u32 dst,
				    int dst_len, struct fib_alias *fa,
				    struct netlink_ext_ack *extack)
{
	struct fib_entry_notifier_info info = {
		.info.extack = extack,
		.dst = dst,
		.dst_len = dst_len,
		.fi = fa->fa_info,
		.tos = fa->fa_tos,
		.type = fa->fa_type,
		.tb_id = fa->tb_id,
	};
	return call_fib4_notifiers(net, event_type, &info.info);
}