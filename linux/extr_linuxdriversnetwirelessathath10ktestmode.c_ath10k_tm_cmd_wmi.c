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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct nlattr {int dummy; } ;
struct ath10k {scalar_t__ state; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_TESTMODE ; 
 scalar_t__ ATH10K_STATE_UTF ; 
 size_t ATH10K_TM_ATTR_DATA ; 
 size_t ATH10K_TM_ATTR_WMI_CMDID ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ath10k_dbg_dump (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,void*,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 int ath10k_wmi_cmd_send (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 

__attribute__((used)) static int ath10k_tm_cmd_wmi(struct ath10k *ar, struct nlattr *tb[])
{
	struct sk_buff *skb;
	int ret, buf_len;
	u32 cmd_id;
	void *buf;

	mutex_lock(&ar->conf_mutex);

	if (ar->state != ATH10K_STATE_UTF) {
		ret = -ENETDOWN;
		goto out;
	}

	if (!tb[ATH10K_TM_ATTR_DATA]) {
		ret = -EINVAL;
		goto out;
	}

	if (!tb[ATH10K_TM_ATTR_WMI_CMDID]) {
		ret = -EINVAL;
		goto out;
	}

	buf = nla_data(tb[ATH10K_TM_ATTR_DATA]);
	buf_len = nla_len(tb[ATH10K_TM_ATTR_DATA]);
	cmd_id = nla_get_u32(tb[ATH10K_TM_ATTR_WMI_CMDID]);

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE,
		   "testmode cmd wmi cmd_id %d buf %pK buf_len %d\n",
		   cmd_id, buf, buf_len);

	ath10k_dbg_dump(ar, ATH10K_DBG_TESTMODE, NULL, "", buf, buf_len);

	skb = ath10k_wmi_alloc_skb(ar, buf_len);
	if (!skb) {
		ret = -ENOMEM;
		goto out;
	}

	memcpy(skb->data, buf, buf_len);

	ret = ath10k_wmi_cmd_send(ar, skb, cmd_id);
	if (ret) {
		ath10k_warn(ar, "failed to transmit wmi command (testmode): %d\n",
			    ret);
		goto out;
	}

	ret = 0;

out:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}