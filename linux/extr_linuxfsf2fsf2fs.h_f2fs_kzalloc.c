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
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_ZERO ; 
 void* f2fs_kmalloc (struct f2fs_sb_info*,size_t,int) ; 

__attribute__((used)) static inline void *f2fs_kzalloc(struct f2fs_sb_info *sbi,
					size_t size, gfp_t flags)
{
	return f2fs_kmalloc(sbi, size, flags | __GFP_ZERO);
}