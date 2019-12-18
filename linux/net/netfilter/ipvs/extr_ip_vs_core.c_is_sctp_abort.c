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
struct sctphdr {int dummy; } ;
struct sctp_chunkhdr {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  schunk ;

/* Variables and functions */
 scalar_t__ SCTP_CID_ABORT ; 
 struct sctp_chunkhdr* skb_header_pointer (struct sk_buff const*,int,int,struct sctp_chunkhdr*) ; 

__attribute__((used)) static inline int is_sctp_abort(const struct sk_buff *skb, int nh_len)
{
	struct sctp_chunkhdr *sch, schunk;
	sch = skb_header_pointer(skb, nh_len + sizeof(struct sctphdr),
				 sizeof(schunk), &schunk);
	if (sch == NULL)
		return 0;
	if (sch->type == SCTP_CID_ABORT)
		return 1;
	return 0;
}