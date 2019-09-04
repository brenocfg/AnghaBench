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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct tx_ts_record {int TxCurSeq; } ;
struct ts_common_info {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  priority; int /*<<< orphan*/  data; } ;
struct rtllib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetTs (struct rtllib_device*,struct ts_common_info**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IsQoSDataFrame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_DIR ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 rtllib_query_seqnum(struct rtllib_device *ieee, struct sk_buff *skb,
			       u8 *dst)
{
	u16 seqnum = 0;

	if (is_multicast_ether_addr(dst))
		return 0;
	if (IsQoSDataFrame(skb->data)) {
		struct tx_ts_record *pTS = NULL;

		if (!GetTs(ieee, (struct ts_common_info **)(&pTS), dst,
		    skb->priority, TX_DIR, true))
			return 0;
		seqnum = pTS->TxCurSeq;
		pTS->TxCurSeq = (pTS->TxCurSeq+1)%4096;
		return seqnum;
	}
	return 0;
}