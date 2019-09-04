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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dropped_frames_no_route; } ;
struct TYPE_5__ {TYPE_1__ mshstats; } ;
struct TYPE_6__ {TYPE_2__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

void mesh_path_discard_frame(struct ieee80211_sub_if_data *sdata,
			     struct sk_buff *skb)
{
	kfree_skb(skb);
	sdata->u.mesh.mshstats.dropped_frames_no_route++;
}