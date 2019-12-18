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
struct mesh_path {int /*<<< orphan*/  sdata; int /*<<< orphan*/  frame_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  mesh_path_discard_frame (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

void mesh_path_flush_pending(struct mesh_path *mpath)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&mpath->frame_queue)) != NULL)
		mesh_path_discard_frame(mpath->sdata, skb);
}