#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct fou {int flags; int /*<<< orphan*/  type; int /*<<< orphan*/  protocol; int /*<<< orphan*/  port; TYPE_2__* sock; } ;
struct TYPE_4__ {TYPE_1__* sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOU_ATTR_AF ; 
 int /*<<< orphan*/  FOU_ATTR_IPPROTO ; 
 int /*<<< orphan*/  FOU_ATTR_PORT ; 
 int /*<<< orphan*/  FOU_ATTR_REMCSUM_NOPARTIAL ; 
 int /*<<< orphan*/  FOU_ATTR_TYPE ; 
 int FOU_F_REMCSUM_NOPARTIAL ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fou_fill_info(struct fou *fou, struct sk_buff *msg)
{
	if (nla_put_u8(msg, FOU_ATTR_AF, fou->sock->sk->sk_family) ||
	    nla_put_be16(msg, FOU_ATTR_PORT, fou->port) ||
	    nla_put_u8(msg, FOU_ATTR_IPPROTO, fou->protocol) ||
	    nla_put_u8(msg, FOU_ATTR_TYPE, fou->type))
		return -1;

	if (fou->flags & FOU_F_REMCSUM_NOPARTIAL)
		if (nla_put_flag(msg, FOU_ATTR_REMCSUM_NOPARTIAL))
			return -1;
	return 0;
}