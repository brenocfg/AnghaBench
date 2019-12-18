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
typedef  int u64 ;
struct ufs_sb_private_info {int s_fmask; int s_fshift; } ;
struct ufs_buffer_head {int fragment; int count; int /*<<< orphan*/ ** bh; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int UFS_MAXFRAG ; 
 struct ufs_buffer_head* USPI_UBH (struct ufs_sb_private_info*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sb_bread (struct super_block*,int) ; 

struct ufs_buffer_head * ubh_bread_uspi (struct ufs_sb_private_info * uspi,
	struct super_block *sb, u64 fragment, u64 size)
{
	unsigned i, j;
	u64 count = 0;
	if (size & ~uspi->s_fmask)
		return NULL;
	count = size >> uspi->s_fshift;
	if (count <= 0 || count > UFS_MAXFRAG)
		return NULL;
	USPI_UBH(uspi)->fragment = fragment;
	USPI_UBH(uspi)->count = count;
	for (i = 0; i < count; i++)
		if (!(USPI_UBH(uspi)->bh[i] = sb_bread(sb, fragment + i)))
			goto failed;
	for (; i < UFS_MAXFRAG; i++)
		USPI_UBH(uspi)->bh[i] = NULL;
	return USPI_UBH(uspi);
failed:
	for (j = 0; j < i; j++)
		brelse (USPI_UBH(uspi)->bh[j]);
	return NULL;
}