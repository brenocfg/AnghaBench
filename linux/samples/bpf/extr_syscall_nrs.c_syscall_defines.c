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

/* Variables and functions */
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  SYSNR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __NR_mmap ; 
 int /*<<< orphan*/  __NR_mmap2 ; 
 int /*<<< orphan*/  __NR_read ; 
 int /*<<< orphan*/  __NR_write ; 

void syscall_defines(void)
{
	COMMENT("Linux system call numbers.");
	SYSNR(__NR_write);
	SYSNR(__NR_read);
#ifdef __NR_mmap2
	SYSNR(__NR_mmap2);
#endif
#ifdef __NR_mmap
	SYSNR(__NR_mmap);
#endif

}