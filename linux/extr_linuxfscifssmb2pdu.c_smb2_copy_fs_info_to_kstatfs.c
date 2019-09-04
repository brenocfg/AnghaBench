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
struct smb2_fs_full_size_info {int /*<<< orphan*/  CallerAvailableAllocationUnits; int /*<<< orphan*/  TotalAllocationUnits; int /*<<< orphan*/  SectorsPerAllocationUnit; int /*<<< orphan*/  BytesPerSector; } ;
struct kstatfs {int f_bsize; void* f_bavail; void* f_bfree; void* f_blocks; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 

void
smb2_copy_fs_info_to_kstatfs(struct smb2_fs_full_size_info *pfs_inf,
			     struct kstatfs *kst)
{
	kst->f_bsize = le32_to_cpu(pfs_inf->BytesPerSector) *
			  le32_to_cpu(pfs_inf->SectorsPerAllocationUnit);
	kst->f_blocks = le64_to_cpu(pfs_inf->TotalAllocationUnits);
	kst->f_bfree  = kst->f_bavail =
			le64_to_cpu(pfs_inf->CallerAvailableAllocationUnits);
	return;
}