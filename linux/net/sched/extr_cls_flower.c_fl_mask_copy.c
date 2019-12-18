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
struct fl_flow_mask {int /*<<< orphan*/  range; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 void* fl_key_get_start (int /*<<< orphan*/ *,struct fl_flow_mask*) ; 
 int /*<<< orphan*/  fl_mask_range (struct fl_flow_mask*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fl_mask_copy(struct fl_flow_mask *dst,
			 struct fl_flow_mask *src)
{
	const void *psrc = fl_key_get_start(&src->key, src);
	void *pdst = fl_key_get_start(&dst->key, src);

	memcpy(pdst, psrc, fl_mask_range(src));
	dst->range = src->range;
}