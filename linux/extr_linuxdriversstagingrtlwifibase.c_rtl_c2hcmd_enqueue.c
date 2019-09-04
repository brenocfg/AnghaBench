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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  c2hcmd_wq; int /*<<< orphan*/  rtl_wq; } ;
struct TYPE_3__ {int /*<<< orphan*/  c2hcmd_lock; } ;
struct rtl_priv {TYPE_2__ works; TYPE_1__ locks; int /*<<< orphan*/  c2hcmd_list; } ;
struct rtl_c2hcmd {int tag; int len; int /*<<< orphan*/  list; void* val; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  kfree (struct rtl_c2hcmd*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rtl_c2hcmd_enqueue(struct ieee80211_hw *hw, u8 tag, u8 len, u8 *val)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	unsigned long flags;
	struct rtl_c2hcmd *c2hcmd;

	c2hcmd = kmalloc(sizeof(*c2hcmd),
			 in_interrupt() ? GFP_ATOMIC : GFP_KERNEL);

	if (!c2hcmd)
		goto label_err;

	c2hcmd->val = kmalloc(len,
			      in_interrupt() ? GFP_ATOMIC : GFP_KERNEL);

	if (!c2hcmd->val)
		goto label_err2;

	/* fill data */
	c2hcmd->tag = tag;
	c2hcmd->len = len;
	memcpy(c2hcmd->val, val, len);

	/* enqueue */
	spin_lock_irqsave(&rtlpriv->locks.c2hcmd_lock, flags);

	list_add_tail(&c2hcmd->list, &rtlpriv->c2hcmd_list);

	spin_unlock_irqrestore(&rtlpriv->locks.c2hcmd_lock, flags);

	/* wake up wq */
	queue_delayed_work(rtlpriv->works.rtl_wq, &rtlpriv->works.c2hcmd_wq, 0);

	return;

label_err2:
	kfree(c2hcmd);

label_err:
	RT_TRACE(rtlpriv, COMP_CMD, DBG_WARNING,
		 "C2H cmd enqueue fail.\n");
}