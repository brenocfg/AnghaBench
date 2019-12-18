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
typedef  int u32 ;
struct tc_u_hnode {int /*<<< orphan*/  handle_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ idr_alloc_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 gen_new_kid(struct tc_u_hnode *ht, u32 htid)
{
	u32 index = htid | 0x800;
	u32 max = htid | 0xFFF;

	if (idr_alloc_u32(&ht->handle_idr, NULL, &index, max, GFP_KERNEL)) {
		index = htid + 1;
		if (idr_alloc_u32(&ht->handle_idr, NULL, &index, max,
				 GFP_KERNEL))
			index = max;
	}

	return index;
}