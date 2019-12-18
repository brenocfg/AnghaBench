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
struct sk_buff {int dummy; } ;
struct ps_data {int dtim_count; int dtim_bc_mc; scalar_t__* tim; int /*<<< orphan*/  bc_buf; int /*<<< orphan*/  num_sta_ps; } ;
struct TYPE_3__ {int dtim_period; } ;
struct TYPE_4__ {TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_MAX_AID ; 
 int IEEE80211_MAX_TIM_LEN ; 
 int /*<<< orphan*/  WLAN_EID_TIM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_empty (unsigned long*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__*,int) ; 
 int* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ieee80211_beacon_add_tim(struct ieee80211_sub_if_data *sdata,
				       struct ps_data *ps, struct sk_buff *skb,
				       bool is_template)
{
	u8 *pos, *tim;
	int aid0 = 0;
	int i, have_bits = 0, n1, n2;

	/* Generate bitmap for TIM only if there are any STAs in power save
	 * mode. */
	if (atomic_read(&ps->num_sta_ps) > 0)
		/* in the hope that this is faster than
		 * checking byte-for-byte */
		have_bits = !bitmap_empty((unsigned long *)ps->tim,
					  IEEE80211_MAX_AID+1);
	if (!is_template) {
		if (ps->dtim_count == 0)
			ps->dtim_count = sdata->vif.bss_conf.dtim_period - 1;
		else
			ps->dtim_count--;
	}

	tim = pos = skb_put(skb, 6);
	*pos++ = WLAN_EID_TIM;
	*pos++ = 4;
	*pos++ = ps->dtim_count;
	*pos++ = sdata->vif.bss_conf.dtim_period;

	if (ps->dtim_count == 0 && !skb_queue_empty(&ps->bc_buf))
		aid0 = 1;

	ps->dtim_bc_mc = aid0 == 1;

	if (have_bits) {
		/* Find largest even number N1 so that bits numbered 1 through
		 * (N1 x 8) - 1 in the bitmap are 0 and number N2 so that bits
		 * (N2 + 1) x 8 through 2007 are 0. */
		n1 = 0;
		for (i = 0; i < IEEE80211_MAX_TIM_LEN; i++) {
			if (ps->tim[i]) {
				n1 = i & 0xfe;
				break;
			}
		}
		n2 = n1;
		for (i = IEEE80211_MAX_TIM_LEN - 1; i >= n1; i--) {
			if (ps->tim[i]) {
				n2 = i;
				break;
			}
		}

		/* Bitmap control */
		*pos++ = n1 | aid0;
		/* Part Virt Bitmap */
		skb_put(skb, n2 - n1);
		memcpy(pos, ps->tim + n1, n2 - n1 + 1);

		tim[1] = n2 - n1 + 4;
	} else {
		*pos++ = aid0; /* Bitmap control */
		*pos++ = 0; /* Part Virt Bitmap */
	}
}