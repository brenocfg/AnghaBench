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
struct datalink_proto {TYPE_2__* sap; } ;
struct TYPE_3__ {int /*<<< orphan*/  lsap; } ;
struct TYPE_4__ {TYPE_1__ laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  llc_build_and_send_ui_pkt (TYPE_2__*,struct sk_buff*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p8022_request(struct datalink_proto *dl, struct sk_buff *skb,
			 unsigned char *dest)
{
	llc_build_and_send_ui_pkt(dl->sap, skb, dest, dl->sap->laddr.lsap);
	return 0;
}