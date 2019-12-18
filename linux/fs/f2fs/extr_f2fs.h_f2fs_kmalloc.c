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
struct f2fs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAULT_KMALLOC ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 void* kvmalloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ time_to_inject (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *f2fs_kmalloc(struct f2fs_sb_info *sbi,
					size_t size, gfp_t flags)
{
	void *ret;

	if (time_to_inject(sbi, FAULT_KMALLOC)) {
		f2fs_show_injection_info(FAULT_KMALLOC);
		return NULL;
	}

	ret = kmalloc(size, flags);
	if (ret)
		return ret;

	return kvmalloc(size, flags);
}