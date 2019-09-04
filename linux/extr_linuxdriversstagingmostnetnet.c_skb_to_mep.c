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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct mbo {unsigned int buffer_length; int /*<<< orphan*/ * virt_address; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HB (unsigned int) ; 
 int /*<<< orphan*/  LB (unsigned int) ; 
 int MEP_DEF_RETRY ; 
 int /*<<< orphan*/  MEP_HDR_LEN ; 
 int /*<<< orphan*/  PMHL ; 
 int PMS_DEF_PRIO ; 
 int PMS_FIFONO_MEP ; 
 int PMS_FIFONO_SHIFT ; 
 int PMS_MSGTYPE_DATA ; 
 int PMS_RETRY_SHIFT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int skb_to_mep(const struct sk_buff *skb, struct mbo *mbo)
{
	u8 *buff = mbo->virt_address;
	unsigned int mep_len = skb->len + MEP_HDR_LEN;

	if (mbo->buffer_length < mep_len) {
		pr_err("drop: too small buffer! (%d for %d)\n",
		       mbo->buffer_length, mep_len);
		return -EINVAL;
	}

	*buff++ = HB(mep_len - 2);
	*buff++ = LB(mep_len - 2);

	*buff++ = PMHL;
	*buff++ = (PMS_FIFONO_MEP << PMS_FIFONO_SHIFT) | PMS_MSGTYPE_DATA;
	*buff++ = (MEP_DEF_RETRY << PMS_RETRY_SHIFT) | PMS_DEF_PRIO;
	*buff++ = 0;
	*buff++ = 0;
	*buff++ = 0;

	memcpy(buff, skb->data, skb->len);
	mbo->buffer_length = mep_len;
	return 0;
}