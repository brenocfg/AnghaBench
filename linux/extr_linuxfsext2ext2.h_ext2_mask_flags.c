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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int __u32 ;

/* Variables and functions */
 int EXT2_OTHER_FLMASK ; 
 int EXT2_REG_FLMASK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __u32 ext2_mask_flags(umode_t mode, __u32 flags)
{
	if (S_ISDIR(mode))
		return flags;
	else if (S_ISREG(mode))
		return flags & EXT2_REG_FLMASK;
	else
		return flags & EXT2_OTHER_FLMASK;
}