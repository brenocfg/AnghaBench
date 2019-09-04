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
struct sctp_chunk {struct sk_buff* skb; } ;
struct TYPE_4__ {TYPE_1__* af; } ;
struct TYPE_3__ {int (* skb_iif ) (struct sk_buff*) ;} ;

/* Variables and functions */
 TYPE_2__* SCTP_INPUT_CB (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 

int sctp_chunk_iif(const struct sctp_chunk *chunk)
{
	struct sk_buff *skb = chunk->skb;

	return SCTP_INPUT_CB(skb)->af->skb_iif(skb);
}