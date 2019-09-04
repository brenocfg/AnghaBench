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
struct vm_area_struct {int dummy; } ;
struct prctl_mm_map {unsigned long start_code; unsigned long end_code; unsigned long start_data; unsigned long end_data; unsigned long start_brk; unsigned long brk; unsigned long start_stack; unsigned long arg_start; unsigned long arg_end; unsigned long env_start; unsigned long env_end; int exe_fd; scalar_t__ auxv_size; int /*<<< orphan*/ * auxv; } ;
struct mm_struct {unsigned long start_code; unsigned long end_code; unsigned long start_data; unsigned long end_data; unsigned long start_brk; unsigned long brk; unsigned long start_stack; unsigned long arg_start; unsigned long arg_end; unsigned long env_start; unsigned long env_end; int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int EFAULT ; 
 int EINVAL ; 
 int EPERM ; 
#define  PR_SET_MM_ARG_END 138 
#define  PR_SET_MM_ARG_START 137 
 int PR_SET_MM_AUXV ; 
#define  PR_SET_MM_BRK 136 
#define  PR_SET_MM_END_CODE 135 
#define  PR_SET_MM_END_DATA 134 
#define  PR_SET_MM_ENV_END 133 
#define  PR_SET_MM_ENV_START 132 
 int PR_SET_MM_EXE_FILE ; 
 int PR_SET_MM_MAP ; 
 int PR_SET_MM_MAP_SIZE ; 
#define  PR_SET_MM_START_BRK 131 
#define  PR_SET_MM_START_CODE 130 
#define  PR_SET_MM_START_DATA 129 
#define  PR_SET_MM_START_STACK 128 
 unsigned long TASK_SIZE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 unsigned long mmap_min_addr ; 
 int prctl_set_auxv (struct mm_struct*,unsigned long,unsigned long) ; 
 int prctl_set_mm_exe_file (struct mm_struct*,unsigned int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int validate_prctl_map (struct prctl_mm_map*) ; 

__attribute__((used)) static int prctl_set_mm(int opt, unsigned long addr,
			unsigned long arg4, unsigned long arg5)
{
	struct mm_struct *mm = current->mm;
	struct prctl_mm_map prctl_map;
	struct vm_area_struct *vma;
	int error;

	if (arg5 || (arg4 && (opt != PR_SET_MM_AUXV &&
			      opt != PR_SET_MM_MAP &&
			      opt != PR_SET_MM_MAP_SIZE)))
		return -EINVAL;

#ifdef CONFIG_CHECKPOINT_RESTORE
	if (opt == PR_SET_MM_MAP || opt == PR_SET_MM_MAP_SIZE)
		return prctl_set_mm_map(opt, (const void __user *)addr, arg4);
#endif

	if (!capable(CAP_SYS_RESOURCE))
		return -EPERM;

	if (opt == PR_SET_MM_EXE_FILE)
		return prctl_set_mm_exe_file(mm, (unsigned int)addr);

	if (opt == PR_SET_MM_AUXV)
		return prctl_set_auxv(mm, addr, arg4);

	if (addr >= TASK_SIZE || addr < mmap_min_addr)
		return -EINVAL;

	error = -EINVAL;

	down_write(&mm->mmap_sem);
	vma = find_vma(mm, addr);

	prctl_map.start_code	= mm->start_code;
	prctl_map.end_code	= mm->end_code;
	prctl_map.start_data	= mm->start_data;
	prctl_map.end_data	= mm->end_data;
	prctl_map.start_brk	= mm->start_brk;
	prctl_map.brk		= mm->brk;
	prctl_map.start_stack	= mm->start_stack;
	prctl_map.arg_start	= mm->arg_start;
	prctl_map.arg_end	= mm->arg_end;
	prctl_map.env_start	= mm->env_start;
	prctl_map.env_end	= mm->env_end;
	prctl_map.auxv		= NULL;
	prctl_map.auxv_size	= 0;
	prctl_map.exe_fd	= -1;

	switch (opt) {
	case PR_SET_MM_START_CODE:
		prctl_map.start_code = addr;
		break;
	case PR_SET_MM_END_CODE:
		prctl_map.end_code = addr;
		break;
	case PR_SET_MM_START_DATA:
		prctl_map.start_data = addr;
		break;
	case PR_SET_MM_END_DATA:
		prctl_map.end_data = addr;
		break;
	case PR_SET_MM_START_STACK:
		prctl_map.start_stack = addr;
		break;
	case PR_SET_MM_START_BRK:
		prctl_map.start_brk = addr;
		break;
	case PR_SET_MM_BRK:
		prctl_map.brk = addr;
		break;
	case PR_SET_MM_ARG_START:
		prctl_map.arg_start = addr;
		break;
	case PR_SET_MM_ARG_END:
		prctl_map.arg_end = addr;
		break;
	case PR_SET_MM_ENV_START:
		prctl_map.env_start = addr;
		break;
	case PR_SET_MM_ENV_END:
		prctl_map.env_end = addr;
		break;
	default:
		goto out;
	}

	error = validate_prctl_map(&prctl_map);
	if (error)
		goto out;

	switch (opt) {
	/*
	 * If command line arguments and environment
	 * are placed somewhere else on stack, we can
	 * set them up here, ARG_START/END to setup
	 * command line argumets and ENV_START/END
	 * for environment.
	 */
	case PR_SET_MM_START_STACK:
	case PR_SET_MM_ARG_START:
	case PR_SET_MM_ARG_END:
	case PR_SET_MM_ENV_START:
	case PR_SET_MM_ENV_END:
		if (!vma) {
			error = -EFAULT;
			goto out;
		}
	}

	mm->start_code	= prctl_map.start_code;
	mm->end_code	= prctl_map.end_code;
	mm->start_data	= prctl_map.start_data;
	mm->end_data	= prctl_map.end_data;
	mm->start_brk	= prctl_map.start_brk;
	mm->brk		= prctl_map.brk;
	mm->start_stack	= prctl_map.start_stack;
	mm->arg_start	= prctl_map.arg_start;
	mm->arg_end	= prctl_map.arg_end;
	mm->env_start	= prctl_map.env_start;
	mm->env_end	= prctl_map.env_end;

	error = 0;
out:
	up_write(&mm->mmap_sem);
	return error;
}