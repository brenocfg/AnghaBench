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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  classid; } ;

/* Variables and functions */
 TYPE_1__* choke_skb_cb (struct sk_buff*) ; 

__attribute__((used)) static inline void choke_set_classid(struct sk_buff *skb, u16 classid)
{
	choke_skb_cb(skb)->classid = classid;
}