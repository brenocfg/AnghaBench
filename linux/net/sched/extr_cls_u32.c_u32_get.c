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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_proto {int /*<<< orphan*/  root; struct tc_u_common* data; } ;
typedef  void tc_u_hnode ;
struct tc_u_common {int dummy; } ;

/* Variables and functions */
 scalar_t__ TC_U32_HTID (int /*<<< orphan*/ ) ; 
 scalar_t__ TC_U32_KEY (int /*<<< orphan*/ ) ; 
 scalar_t__ TC_U32_ROOT ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 void* u32_lookup_ht (struct tc_u_common*,scalar_t__) ; 
 void* u32_lookup_key (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *u32_get(struct tcf_proto *tp, u32 handle)
{
	struct tc_u_hnode *ht;
	struct tc_u_common *tp_c = tp->data;

	if (TC_U32_HTID(handle) == TC_U32_ROOT)
		ht = rtnl_dereference(tp->root);
	else
		ht = u32_lookup_ht(tp_c, TC_U32_HTID(handle));

	if (!ht)
		return NULL;

	if (TC_U32_KEY(handle) == 0)
		return ht;

	return u32_lookup_key(ht, handle);
}