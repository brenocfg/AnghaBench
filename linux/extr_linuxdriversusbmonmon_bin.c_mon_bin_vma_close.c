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
struct vm_area_struct {struct mon_reader_bin* vm_private_data; } ;
struct mon_reader_bin {int /*<<< orphan*/  mmap_active; } ;

/* Variables and functions */

__attribute__((used)) static void mon_bin_vma_close(struct vm_area_struct *vma)
{
	struct mon_reader_bin *rp = vma->vm_private_data;
	rp->mmap_active--;
}