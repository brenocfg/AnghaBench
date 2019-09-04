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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {TYPE_1__* cmd; TYPE_2__* ops; } ;
struct ath10k {TYPE_3__ wmi; } ;
struct TYPE_5__ {struct sk_buff* (* gen_wow_add_pattern ) (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  wow_add_wake_pattern_cmdid; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int ath10k_wmi_cmd_send (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static inline int
ath10k_wmi_wow_add_pattern(struct ath10k *ar, u32 vdev_id, u32 pattern_id,
			   const u8 *pattern, const u8 *mask,
			   int pattern_len, int pattern_offset)
{
	struct sk_buff *skb;
	u32 cmd_id;

	if (!ar->wmi.ops->gen_wow_add_pattern)
		return -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_wow_add_pattern(ar, vdev_id, pattern_id,
					       pattern, mask, pattern_len,
					       pattern_offset);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->wow_add_wake_pattern_cmdid;
	return ath10k_wmi_cmd_send(ar, skb, cmd_id);
}