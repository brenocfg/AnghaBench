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
struct uuid_module {int max_instance; int /*<<< orphan*/ * pvt_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_INSTANCE_BUFF ; 
 int skl_getid_32 (struct uuid_module*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int skl_pvtid_128(struct uuid_module *module)
{
	int j, i, word1_mask, word2_mask = 0, pvt_id;

	for (j = 0; j < MAX_INSTANCE_BUFF; j++) {
		word1_mask = 0;

		for (i = 0; i < 2; i++) {
			pvt_id = skl_getid_32(module, &module->pvt_id[j],
						word1_mask, word2_mask);
			if (pvt_id >= 0)
				return pvt_id;

			word1_mask += 32;
			if ((word1_mask + word2_mask) >= module->max_instance)
				return -EINVAL;
		}

		word2_mask += 64;
		if (word2_mask >= module->max_instance)
			return -EINVAL;
	}

	return -EINVAL;
}