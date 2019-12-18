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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_TPMETER_COOKIE ; 
 int ENOBUFS ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
batadv_netlink_tp_meter_put(struct sk_buff *msg, u32 cookie)
{
	if (nla_put_u32(msg, BATADV_ATTR_TPMETER_COOKIE, cookie))
		return -ENOBUFS;

	return 0;
}