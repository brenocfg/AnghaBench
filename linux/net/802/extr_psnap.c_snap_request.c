#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct datalink_proto {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  lsap; } ;
struct TYPE_5__ {TYPE_1__ laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  llc_build_and_send_ui_pkt (TYPE_2__*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 TYPE_2__* snap_sap ; 

__attribute__((used)) static int snap_request(struct datalink_proto *dl,
			struct sk_buff *skb, u8 *dest)
{
	memcpy(skb_push(skb, 5), dl->type, 5);
	llc_build_and_send_ui_pkt(snap_sap, skb, dest, snap_sap->laddr.lsap);
	return 0;
}