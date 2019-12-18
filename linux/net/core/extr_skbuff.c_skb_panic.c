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
struct sk_buff {TYPE_1__* dev; scalar_t__ end; scalar_t__ tail; int /*<<< orphan*/  data; int /*<<< orphan*/  head; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  pr_emerg (char*,char const*,void*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long,char*) ; 

__attribute__((used)) static void skb_panic(struct sk_buff *skb, unsigned int sz, void *addr,
		      const char msg[])
{
	pr_emerg("%s: text:%p len:%d put:%d head:%p data:%p tail:%#lx end:%#lx dev:%s\n",
		 msg, addr, skb->len, sz, skb->head, skb->data,
		 (unsigned long)skb->tail, (unsigned long)skb->end,
		 skb->dev ? skb->dev->name : "<NULL>");
	BUG();
}