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
struct ath10k_wmi {TYPE_2__* cmd; TYPE_1__* ops; } ;
struct ath10k {struct ath10k_wmi wmi; } ;
typedef  enum wmi_bss_survey_req_type { ____Placeholder_wmi_bss_survey_req_type } wmi_bss_survey_req_type ;
struct TYPE_4__ {int /*<<< orphan*/  pdev_bss_chan_info_request_cmdid; } ;
struct TYPE_3__ {struct sk_buff* (* gen_pdev_bss_chan_info_req ) (struct ath10k*,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int ath10k_wmi_cmd_send (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (struct ath10k*,int) ; 

__attribute__((used)) static inline int
ath10k_wmi_pdev_bss_chan_info_request(struct ath10k *ar,
				      enum wmi_bss_survey_req_type type)
{
	struct ath10k_wmi *wmi = &ar->wmi;
	struct sk_buff *skb;

	if (!wmi->ops->gen_pdev_bss_chan_info_req)
		return -EOPNOTSUPP;

	skb = wmi->ops->gen_pdev_bss_chan_info_req(ar, type);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	return ath10k_wmi_cmd_send(ar, skb,
				   wmi->cmd->pdev_bss_chan_info_request_cmdid);
}