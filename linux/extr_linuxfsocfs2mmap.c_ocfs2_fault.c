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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int /*<<< orphan*/  pgoff; int /*<<< orphan*/  page; struct vm_area_struct* vma; } ;
struct vm_area_struct {TYPE_2__* vm_file; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_6__ {int /*<<< orphan*/  ip_blkno; } ;
struct TYPE_5__ {TYPE_1__* f_mapping; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_3__* OCFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemap_fault (struct vm_fault*) ; 
 int /*<<< orphan*/  ocfs2_block_signals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_unblock_signals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_fault (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t ocfs2_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	sigset_t oldset;
	vm_fault_t ret;

	ocfs2_block_signals(&oldset);
	ret = filemap_fault(vmf);
	ocfs2_unblock_signals(&oldset);

	trace_ocfs2_fault(OCFS2_I(vma->vm_file->f_mapping->host)->ip_blkno,
			  vma, vmf->page, vmf->pgoff);
	return ret;
}