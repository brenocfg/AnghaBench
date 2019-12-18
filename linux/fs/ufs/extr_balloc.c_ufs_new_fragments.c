#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ufs_super_block_first {void* fs_optim; } ;
struct TYPE_4__ {scalar_t__ cs_nffree; } ;
struct ufs_sb_private_info {unsigned int s_fpb; scalar_t__ s_root_blocks; scalar_t__ s_size; scalar_t__ s_space_to_time; scalar_t__ s_time_to_space; scalar_t__ s_sbbase; TYPE_1__ cs_total; } ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct TYPE_6__ {scalar_t__ i_lastfrag; int /*<<< orphan*/  meta_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_lock; struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int ENOSPC ; 
 scalar_t__ INVBLOCK ; 
 int /*<<< orphan*/  UFSD (char*,...) ; 
 TYPE_3__* UFS_I (struct inode*) ; 
 scalar_t__ UFS_OPTSPACE ; 
 scalar_t__ UFS_OPTTIME ; 
 TYPE_2__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 void* cpu_to_fs32 (struct super_block*,scalar_t__) ; 
 scalar_t__ fs32_to_cpu (struct super_block*,void*) ; 
 void* max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_seqlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_sequnlock_excl (int /*<<< orphan*/ *) ; 
 struct ufs_super_block_first* ubh_get_usb_first (struct ufs_sb_private_info*) ; 
 scalar_t__ ufs_add_fragments (struct inode*,scalar_t__,unsigned int,unsigned int) ; 
 scalar_t__ ufs_alloc_fragments (struct inode*,unsigned int,scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  ufs_change_blocknr (struct inode*,scalar_t__,unsigned int,scalar_t__,scalar_t__,struct page*) ; 
 int /*<<< orphan*/  ufs_clear_frags (struct inode*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_cpu_to_data_ptr (struct super_block*,void*,scalar_t__) ; 
 scalar_t__ ufs_data_ptr_to_cpu (struct super_block*,void*) ; 
 unsigned int ufs_dtog (struct ufs_sb_private_info*,scalar_t__) ; 
 int /*<<< orphan*/  ufs_error (struct super_block*,char*,char*,unsigned long long,unsigned long long) ; 
 unsigned int ufs_fragnum (scalar_t__) ; 
 int /*<<< orphan*/  ufs_free_fragments (struct inode*,scalar_t__,unsigned int) ; 
 scalar_t__ ufs_freefrags (struct ufs_sb_private_info*) ; 
 unsigned int ufs_inotocg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_warning (struct super_block*,char*,char*,unsigned long long,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

u64 ufs_new_fragments(struct inode *inode, void *p, u64 fragment,
			   u64 goal, unsigned count, int *err,
			   struct page *locked_page)
{
	struct super_block * sb;
	struct ufs_sb_private_info * uspi;
	struct ufs_super_block_first * usb1;
	unsigned cgno, oldcount, newcount;
	u64 tmp, request, result;
	
	UFSD("ENTER, ino %lu, fragment %llu, goal %llu, count %u\n",
	     inode->i_ino, (unsigned long long)fragment,
	     (unsigned long long)goal, count);
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	usb1 = ubh_get_usb_first(uspi);
	*err = -ENOSPC;

	mutex_lock(&UFS_SB(sb)->s_lock);
	tmp = ufs_data_ptr_to_cpu(sb, p);

	if (count + ufs_fragnum(fragment) > uspi->s_fpb) {
		ufs_warning(sb, "ufs_new_fragments", "internal warning"
			    " fragment %llu, count %u",
			    (unsigned long long)fragment, count);
		count = uspi->s_fpb - ufs_fragnum(fragment); 
	}
	oldcount = ufs_fragnum (fragment);
	newcount = oldcount + count;

	/*
	 * Somebody else has just allocated our fragments
	 */
	if (oldcount) {
		if (!tmp) {
			ufs_error(sb, "ufs_new_fragments", "internal error, "
				  "fragment %llu, tmp %llu\n",
				  (unsigned long long)fragment,
				  (unsigned long long)tmp);
			mutex_unlock(&UFS_SB(sb)->s_lock);
			return INVBLOCK;
		}
		if (fragment < UFS_I(inode)->i_lastfrag) {
			UFSD("EXIT (ALREADY ALLOCATED)\n");
			mutex_unlock(&UFS_SB(sb)->s_lock);
			return 0;
		}
	}
	else {
		if (tmp) {
			UFSD("EXIT (ALREADY ALLOCATED)\n");
			mutex_unlock(&UFS_SB(sb)->s_lock);
			return 0;
		}
	}

	/*
	 * There is not enough space for user on the device
	 */
	if (unlikely(ufs_freefrags(uspi) <= uspi->s_root_blocks)) {
		if (!capable(CAP_SYS_RESOURCE)) {
			mutex_unlock(&UFS_SB(sb)->s_lock);
			UFSD("EXIT (FAILED)\n");
			return 0;
		}
	}

	if (goal >= uspi->s_size) 
		goal = 0;
	if (goal == 0) 
		cgno = ufs_inotocg (inode->i_ino);
	else
		cgno = ufs_dtog(uspi, goal);
	 
	/*
	 * allocate new fragment
	 */
	if (oldcount == 0) {
		result = ufs_alloc_fragments (inode, cgno, goal, count, err);
		if (result) {
			ufs_clear_frags(inode, result + oldcount,
					newcount - oldcount, locked_page != NULL);
			*err = 0;
			write_seqlock(&UFS_I(inode)->meta_lock);
			ufs_cpu_to_data_ptr(sb, p, result);
			UFS_I(inode)->i_lastfrag =
				max(UFS_I(inode)->i_lastfrag, fragment + count);
			write_sequnlock(&UFS_I(inode)->meta_lock);
		}
		mutex_unlock(&UFS_SB(sb)->s_lock);
		UFSD("EXIT, result %llu\n", (unsigned long long)result);
		return result;
	}

	/*
	 * resize block
	 */
	result = ufs_add_fragments(inode, tmp, oldcount, newcount);
	if (result) {
		*err = 0;
		read_seqlock_excl(&UFS_I(inode)->meta_lock);
		UFS_I(inode)->i_lastfrag = max(UFS_I(inode)->i_lastfrag,
						fragment + count);
		read_sequnlock_excl(&UFS_I(inode)->meta_lock);
		ufs_clear_frags(inode, result + oldcount, newcount - oldcount,
				locked_page != NULL);
		mutex_unlock(&UFS_SB(sb)->s_lock);
		UFSD("EXIT, result %llu\n", (unsigned long long)result);
		return result;
	}

	/*
	 * allocate new block and move data
	 */
	if (fs32_to_cpu(sb, usb1->fs_optim) == UFS_OPTSPACE) {
		request = newcount;
		if (uspi->cs_total.cs_nffree < uspi->s_space_to_time)
			usb1->fs_optim = cpu_to_fs32(sb, UFS_OPTTIME);
	} else {
		request = uspi->s_fpb;
		if (uspi->cs_total.cs_nffree > uspi->s_time_to_space)
			usb1->fs_optim = cpu_to_fs32(sb, UFS_OPTSPACE);
	}
	result = ufs_alloc_fragments (inode, cgno, goal, request, err);
	if (result) {
		ufs_clear_frags(inode, result + oldcount, newcount - oldcount,
				locked_page != NULL);
		mutex_unlock(&UFS_SB(sb)->s_lock);
		ufs_change_blocknr(inode, fragment - oldcount, oldcount,
				   uspi->s_sbbase + tmp,
				   uspi->s_sbbase + result, locked_page);
		*err = 0;
		write_seqlock(&UFS_I(inode)->meta_lock);
		ufs_cpu_to_data_ptr(sb, p, result);
		UFS_I(inode)->i_lastfrag = max(UFS_I(inode)->i_lastfrag,
						fragment + count);
		write_sequnlock(&UFS_I(inode)->meta_lock);
		if (newcount < request)
			ufs_free_fragments (inode, result + newcount, request - newcount);
		ufs_free_fragments (inode, tmp, oldcount);
		UFSD("EXIT, result %llu\n", (unsigned long long)result);
		return result;
	}

	mutex_unlock(&UFS_SB(sb)->s_lock);
	UFSD("EXIT (FAILED)\n");
	return 0;
}