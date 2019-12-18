#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ufs_sb_private_info {unsigned int s_fpb; } ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  __fs32 ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  fs32_add (struct super_block*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void ufs_fragacct (struct super_block * sb, unsigned blockmap,
	__fs32 * fraglist, int cnt)
{
	struct ufs_sb_private_info * uspi;
	unsigned fragsize, pos;
	
	uspi = UFS_SB(sb)->s_uspi;
	
	fragsize = 0;
	for (pos = 0; pos < uspi->s_fpb; pos++) {
		if (blockmap & (1 << pos)) {
			fragsize++;
		}
		else if (fragsize > 0) {
			fs32_add(sb, &fraglist[fragsize], cnt);
			fragsize = 0;
		}
	}
	if (fragsize > 0 && fragsize < uspi->s_fpb)
		fs32_add(sb, &fraglist[fragsize], cnt);
}