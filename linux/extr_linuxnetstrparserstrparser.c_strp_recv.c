#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct strparser {TYPE_2__* sk; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_8__ {TYPE_1__ arg; } ;
typedef  TYPE_3__ read_descriptor_t ;
struct TYPE_7__ {int /*<<< orphan*/  sk_rcvtimeo; int /*<<< orphan*/  sk_rcvbuf; } ;

/* Variables and functions */
 int __strp_recv (TYPE_3__*,struct sk_buff*,unsigned int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int strp_recv(read_descriptor_t *desc, struct sk_buff *orig_skb,
		     unsigned int orig_offset, size_t orig_len)
{
	struct strparser *strp = (struct strparser *)desc->arg.data;

	return __strp_recv(desc, orig_skb, orig_offset, orig_len,
			   strp->sk->sk_rcvbuf, strp->sk->sk_rcvtimeo);
}