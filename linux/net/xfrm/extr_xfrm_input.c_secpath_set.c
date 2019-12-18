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
struct sec_path {scalar_t__ len; scalar_t__ olen; int /*<<< orphan*/  ovec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKB_EXT_SEC_PATH ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sec_path* skb_ext_add (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sec_path* skb_ext_find (struct sk_buff*,int /*<<< orphan*/ ) ; 

struct sec_path *secpath_set(struct sk_buff *skb)
{
	struct sec_path *sp, *tmp = skb_ext_find(skb, SKB_EXT_SEC_PATH);

	sp = skb_ext_add(skb, SKB_EXT_SEC_PATH);
	if (!sp)
		return NULL;

	if (tmp) /* reused existing one (was COW'd if needed) */
		return sp;

	/* allocated new secpath */
	memset(sp->ovec, 0, sizeof(sp->ovec));
	sp->olen = 0;
	sp->len = 0;

	return sp;
}