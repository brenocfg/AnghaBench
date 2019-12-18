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
struct vm_area_struct {struct file* vm_file; } ;
struct kernfs_open_file {int /*<<< orphan*/  kn; TYPE_1__* vm_ops; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* open ) (struct vm_area_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kernfs_get_active (int /*<<< orphan*/ ) ; 
 struct kernfs_open_file* kernfs_of (struct file*) ; 
 int /*<<< orphan*/  kernfs_put_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vm_area_struct*) ; 

__attribute__((used)) static void kernfs_vma_open(struct vm_area_struct *vma)
{
	struct file *file = vma->vm_file;
	struct kernfs_open_file *of = kernfs_of(file);

	if (!of->vm_ops)
		return;

	if (!kernfs_get_active(of->kn))
		return;

	if (of->vm_ops->open)
		of->vm_ops->open(vma);

	kernfs_put_active(of->kn);
}