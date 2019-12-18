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
struct strparser {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {struct strparser* data; } ;
struct TYPE_5__ {TYPE_1__ arg; } ;
typedef  TYPE_2__ read_descriptor_t ;

/* Variables and functions */
 int __strp_recv (TYPE_2__*,struct sk_buff*,unsigned int,size_t,size_t,long) ; 

int strp_process(struct strparser *strp, struct sk_buff *orig_skb,
		 unsigned int orig_offset, size_t orig_len,
		 size_t max_msg_size, long timeo)
{
	read_descriptor_t desc; /* Dummy arg to strp_recv */

	desc.arg.data = strp;

	return __strp_recv(&desc, orig_skb, orig_offset, orig_len,
			   max_msg_size, timeo);
}