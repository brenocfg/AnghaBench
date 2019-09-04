#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff_head {int dummy; } ;
struct sk_buff {struct sk_buff* next; } ;
struct sctp_ulpq {TYPE_2__* asoc; } ;
struct sctp_ulpevent {int /*<<< orphan*/  tsn; } ;
struct sctp_tsnmap {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  scalar_t__ __u16 ;
struct TYPE_6__ {struct sk_buff* frag_list; } ;
struct TYPE_4__ {struct sctp_tsnmap tsn_map; } ;
struct TYPE_5__ {TYPE_1__ peer; } ;

/* Variables and functions */
 scalar_t__ TSN_lte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,struct sk_buff_head*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_tsnmap_get_ctsn (struct sctp_tsnmap*) ; 
 int /*<<< orphan*/  sctp_tsnmap_renege (struct sctp_tsnmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_free (struct sctp_ulpevent*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 struct sk_buff* skb_peek_tail (struct sk_buff_head*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 

__u16 sctp_ulpq_renege_list(struct sctp_ulpq *ulpq, struct sk_buff_head *list,
			    __u16 needed)
{
	__u16 freed = 0;
	__u32 tsn, last_tsn;
	struct sk_buff *skb, *flist, *last;
	struct sctp_ulpevent *event;
	struct sctp_tsnmap *tsnmap;

	tsnmap = &ulpq->asoc->peer.tsn_map;

	while ((skb = skb_peek_tail(list)) != NULL) {
		event = sctp_skb2event(skb);
		tsn = event->tsn;

		/* Don't renege below the Cumulative TSN ACK Point. */
		if (TSN_lte(tsn, sctp_tsnmap_get_ctsn(tsnmap)))
			break;

		/* Events in ordering queue may have multiple fragments
		 * corresponding to additional TSNs.  Sum the total
		 * freed space; find the last TSN.
		 */
		freed += skb_headlen(skb);
		flist = skb_shinfo(skb)->frag_list;
		for (last = flist; flist; flist = flist->next) {
			last = flist;
			freed += skb_headlen(last);
		}
		if (last)
			last_tsn = sctp_skb2event(last)->tsn;
		else
			last_tsn = tsn;

		/* Unlink the event, then renege all applicable TSNs. */
		__skb_unlink(skb, list);
		sctp_ulpevent_free(event);
		while (TSN_lte(tsn, last_tsn)) {
			sctp_tsnmap_renege(tsnmap, tsn);
			tsn++;
		}
		if (freed >= needed)
			return freed;
	}

	return freed;
}