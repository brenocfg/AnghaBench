#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct f2fs_sb_info {scalar_t__ gc_thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  fault_info; } ;
struct TYPE_3__ {scalar_t__ dcc_info; } ;

/* Variables and functions */
 int DCC_INFO ; 
 TYPE_2__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int F2FS_SBI ; 
 int FAULT_INFO_RATE ; 
 int FAULT_INFO_TYPE ; 
 int GC_THREAD ; 
 scalar_t__ NM_I (struct f2fs_sb_info*) ; 
 int NM_INFO ; 
 int RESERVED_BLOCKS ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int SM_INFO ; 

__attribute__((used)) static unsigned char *__struct_ptr(struct f2fs_sb_info *sbi, int struct_type)
{
	if (struct_type == GC_THREAD)
		return (unsigned char *)sbi->gc_thread;
	else if (struct_type == SM_INFO)
		return (unsigned char *)SM_I(sbi);
	else if (struct_type == DCC_INFO)
		return (unsigned char *)SM_I(sbi)->dcc_info;
	else if (struct_type == NM_INFO)
		return (unsigned char *)NM_I(sbi);
	else if (struct_type == F2FS_SBI || struct_type == RESERVED_BLOCKS)
		return (unsigned char *)sbi;
#ifdef CONFIG_F2FS_FAULT_INJECTION
	else if (struct_type == FAULT_INFO_RATE ||
					struct_type == FAULT_INFO_TYPE)
		return (unsigned char *)&F2FS_OPTION(sbi).fault_info;
#endif
	return NULL;
}