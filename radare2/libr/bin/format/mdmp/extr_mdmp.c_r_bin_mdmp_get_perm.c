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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct r_bin_mdmp_obj {int dummy; } ;
struct minidump_memory_info {int protect; } ;

/* Variables and functions */
#define  MINIDUMP_PAGE_EXECUTE 138 
#define  MINIDUMP_PAGE_EXECUTE_READ 137 
#define  MINIDUMP_PAGE_EXECUTE_READWRITE 136 
#define  MINIDUMP_PAGE_EXECUTE_WRITECOPY 135 
#define  MINIDUMP_PAGE_GUARD 134 
#define  MINIDUMP_PAGE_NOACCESS 133 
#define  MINIDUMP_PAGE_NOCACHE 132 
#define  MINIDUMP_PAGE_READONLY 131 
#define  MINIDUMP_PAGE_READWRITE 130 
#define  MINIDUMP_PAGE_WRITECOMBINE 129 
#define  MINIDUMP_PAGE_WRITECOPY 128 
 int /*<<< orphan*/  R_PERM_R ; 
 int /*<<< orphan*/  R_PERM_RW ; 
 int /*<<< orphan*/  R_PERM_RWX ; 
 int /*<<< orphan*/  R_PERM_RX ; 
 int /*<<< orphan*/  R_PERM_X ; 
 struct minidump_memory_info* r_bin_mdmp_get_mem_info (struct r_bin_mdmp_obj*,int /*<<< orphan*/ ) ; 

ut32 r_bin_mdmp_get_perm(struct r_bin_mdmp_obj *obj, ut64 vaddr) {
	struct minidump_memory_info *mem_info;

	if (!(mem_info = r_bin_mdmp_get_mem_info(obj, vaddr))) {
		/* if there is no mem info in the dump, assume default permission */
		return R_PERM_R;
	}

	/* FIXME: Have I got these mappings right, I am not sure I have!!! */

	switch (mem_info->protect) {
	case MINIDUMP_PAGE_READONLY:
		return R_PERM_R;
	case MINIDUMP_PAGE_READWRITE:
		return R_PERM_RW;
	case MINIDUMP_PAGE_EXECUTE:
		return R_PERM_X;
	case MINIDUMP_PAGE_EXECUTE_READ:
		return R_PERM_RX;
	case MINIDUMP_PAGE_EXECUTE_READWRITE:
		return R_PERM_RWX;
	case MINIDUMP_PAGE_NOACCESS:
	case MINIDUMP_PAGE_WRITECOPY:
	case MINIDUMP_PAGE_EXECUTE_WRITECOPY:
	case MINIDUMP_PAGE_GUARD:
	case MINIDUMP_PAGE_NOCACHE:
	case MINIDUMP_PAGE_WRITECOMBINE:
	default:
		return 0;
	}
}