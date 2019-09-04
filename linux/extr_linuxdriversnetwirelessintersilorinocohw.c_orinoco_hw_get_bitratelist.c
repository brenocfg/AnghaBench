#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hermes {TYPE_1__* ops; } ;
struct orinoco_private {struct hermes hw; } ;
struct hermes_idstring {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
typedef  unsigned char s32 ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_2__ {int (* read_ltv ) (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct hermes_idstring*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HERMES_RID_SUPPORTEDDATARATES ; 
 int /*<<< orphan*/  USER_BAP ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 
 int stub1 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct hermes_idstring*) ; 

int orinoco_hw_get_bitratelist(struct orinoco_private *priv,
			       int *numrates, s32 *rates, int max)
{
	struct hermes *hw = &priv->hw;
	struct hermes_idstring list;
	unsigned char *p = (unsigned char *)&list.val;
	int err = 0;
	int num;
	int i;
	unsigned long flags;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	err = hw->ops->read_ltv(hw, USER_BAP, HERMES_RID_SUPPORTEDDATARATES,
				sizeof(list), NULL, &list);
	orinoco_unlock(priv, &flags);

	if (err)
		return err;

	num = le16_to_cpu(list.len);
	*numrates = num;
	num = min(num, max);

	for (i = 0; i < num; i++)
		rates[i] = (p[i] & 0x7f) * 500000; /* convert to bps */

	return 0;
}