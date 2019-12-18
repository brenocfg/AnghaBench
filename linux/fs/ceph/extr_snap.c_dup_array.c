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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  get_unaligned_le64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dup_array(u64 **dst, __le64 *src, u32 num)
{
	u32 i;

	kfree(*dst);
	if (num) {
		*dst = kcalloc(num, sizeof(u64), GFP_NOFS);
		if (!*dst)
			return -ENOMEM;
		for (i = 0; i < num; i++)
			(*dst)[i] = get_unaligned_le64(src + i);
	} else {
		*dst = NULL;
	}
	return 0;
}