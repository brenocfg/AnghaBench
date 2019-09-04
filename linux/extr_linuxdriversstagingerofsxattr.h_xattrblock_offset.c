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
struct erofs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 unsigned int EROFS_BLKSIZ ; 

__attribute__((used)) static inline unsigned
xattrblock_offset(struct erofs_sb_info *sbi, unsigned xattr_id)
{
	return (xattr_id * sizeof(__u32)) % EROFS_BLKSIZ;
}