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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ skb_copy_ubufs (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_uarg (struct sk_buff*) ; 
 scalar_t__ skb_zcopy (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_zcopy_set (struct sk_buff*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int skb_zerocopy_clone(struct sk_buff *nskb, struct sk_buff *orig,
			      gfp_t gfp_mask)
{
	if (skb_zcopy(orig)) {
		if (skb_zcopy(nskb)) {
			/* !gfp_mask callers are verified to !skb_zcopy(nskb) */
			if (!gfp_mask) {
				WARN_ON_ONCE(1);
				return -ENOMEM;
			}
			if (skb_uarg(nskb) == skb_uarg(orig))
				return 0;
			if (skb_copy_ubufs(nskb, GFP_ATOMIC))
				return -EIO;
		}
		skb_zcopy_set(nskb, skb_uarg(orig), NULL);
	}
	return 0;
}