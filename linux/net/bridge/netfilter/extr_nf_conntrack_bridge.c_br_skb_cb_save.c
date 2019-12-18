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
struct sk_buff {int /*<<< orphan*/  cb; } ;
struct br_input_skb_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct br_input_skb_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void br_skb_cb_save(struct sk_buff *skb, struct br_input_skb_cb *cb,
			   size_t inet_skb_parm_size)
{
	memcpy(cb, skb->cb, sizeof(*cb));
	memset(skb->cb, 0, inet_skb_parm_size);
}