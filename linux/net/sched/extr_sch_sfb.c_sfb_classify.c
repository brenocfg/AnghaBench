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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_result {int /*<<< orphan*/  classid; } ;
struct tcf_proto {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
#define  TC_ACT_QUEUED 131 
#define  TC_ACT_SHOT 130 
#define  TC_ACT_STOLEN 129 
#define  TC_ACT_TRAP 128 
 int /*<<< orphan*/  TC_H_MIN (int /*<<< orphan*/ ) ; 
 int __NET_XMIT_STOLEN ; 
 int tcf_classify (struct sk_buff*,struct tcf_proto*,struct tcf_result*,int) ; 

__attribute__((used)) static bool sfb_classify(struct sk_buff *skb, struct tcf_proto *fl,
			 int *qerr, u32 *salt)
{
	struct tcf_result res;
	int result;

	result = tcf_classify(skb, fl, &res, false);
	if (result >= 0) {
#ifdef CONFIG_NET_CLS_ACT
		switch (result) {
		case TC_ACT_STOLEN:
		case TC_ACT_QUEUED:
		case TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			/* fall through */
		case TC_ACT_SHOT:
			return false;
		}
#endif
		*salt = TC_H_MIN(res.classid);
		return true;
	}
	return false;
}