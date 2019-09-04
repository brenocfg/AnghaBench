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
struct fq_tin {int dummy; } ;
struct txq_info {struct fq_tin tin; } ;
struct sk_buff {int dummy; } ;
struct fq {int dummy; } ;
struct ieee80211_local {struct fq fq; } ;

/* Variables and functions */
 int /*<<< orphan*/  fq_flow_get_default_func ; 
 int /*<<< orphan*/  fq_skb_free_func ; 
 int /*<<< orphan*/  fq_tin_enqueue (struct fq*,struct fq_tin*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_set_skb_enqueue_time (struct sk_buff*) ; 

__attribute__((used)) static void ieee80211_txq_enqueue(struct ieee80211_local *local,
				  struct txq_info *txqi,
				  struct sk_buff *skb)
{
	struct fq *fq = &local->fq;
	struct fq_tin *tin = &txqi->tin;

	ieee80211_set_skb_enqueue_time(skb);
	fq_tin_enqueue(fq, tin, skb,
		       fq_skb_free_func,
		       fq_flow_get_default_func);
}