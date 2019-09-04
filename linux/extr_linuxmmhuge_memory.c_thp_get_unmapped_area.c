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
struct file {TYPE_1__* f_mapping; } ;
typedef  int loff_t ;
struct TYPE_6__ {TYPE_2__* mm; } ;
struct TYPE_5__ {unsigned long (* get_unmapped_area ) (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_FS_DAX_PMD ; 
 int /*<<< orphan*/  IS_DAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PMD_SIZE ; 
 unsigned long __thp_get_unmapped_area (struct file*,unsigned long,int,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 unsigned long stub1 (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

unsigned long thp_get_unmapped_area(struct file *filp, unsigned long addr,
		unsigned long len, unsigned long pgoff, unsigned long flags)
{
	loff_t off = (loff_t)pgoff << PAGE_SHIFT;

	if (addr)
		goto out;
	if (!IS_DAX(filp->f_mapping->host) || !IS_ENABLED(CONFIG_FS_DAX_PMD))
		goto out;

	addr = __thp_get_unmapped_area(filp, len, off, flags, PMD_SIZE);
	if (addr)
		return addr;

 out:
	return current->mm->get_unmapped_area(filp, addr, len, pgoff, flags);
}