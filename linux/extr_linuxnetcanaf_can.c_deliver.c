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
struct sk_buff {int dummy; } ;
struct receiver {int /*<<< orphan*/  matches; int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (struct sk_buff*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void deliver(struct sk_buff *skb, struct receiver *r)
{
	r->func(skb, r->data);
	r->matches++;
}