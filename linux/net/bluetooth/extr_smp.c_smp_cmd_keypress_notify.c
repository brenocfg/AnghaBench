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
struct smp_cmd_keypress_notify {int /*<<< orphan*/  value; } ;
struct sk_buff {scalar_t__ data; } ;
struct l2cap_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smp_cmd_keypress_notify(struct l2cap_conn *conn,
				   struct sk_buff *skb)
{
	struct smp_cmd_keypress_notify *kp = (void *) skb->data;

	BT_DBG("value 0x%02x", kp->value);

	return 0;
}