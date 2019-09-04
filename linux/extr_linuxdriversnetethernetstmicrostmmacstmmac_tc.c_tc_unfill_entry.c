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
struct tc_cls_u32_offload {int dummy; } ;
struct stmmac_tc_entry {int in_use; int is_frag; struct stmmac_tc_entry* frag_ptr; } ;
struct stmmac_priv {int dummy; } ;

/* Variables and functions */
 struct stmmac_tc_entry* tc_find_entry (struct stmmac_priv*,struct tc_cls_u32_offload*,int) ; 

__attribute__((used)) static void tc_unfill_entry(struct stmmac_priv *priv,
			    struct tc_cls_u32_offload *cls)
{
	struct stmmac_tc_entry *entry;

	entry = tc_find_entry(priv, cls, false);
	if (!entry)
		return;

	entry->in_use = false;
	if (entry->frag_ptr) {
		entry = entry->frag_ptr;
		entry->is_frag = false;
		entry->in_use = false;
	}
}