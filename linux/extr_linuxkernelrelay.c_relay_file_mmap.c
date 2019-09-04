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
struct vm_area_struct {int dummy; } ;
struct rchan_buf {int dummy; } ;
struct file {struct rchan_buf* private_data; } ;

/* Variables and functions */
 int relay_mmap_buf (struct rchan_buf*,struct vm_area_struct*) ; 

__attribute__((used)) static int relay_file_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct rchan_buf *buf = filp->private_data;
	return relay_mmap_buf(buf, vma);
}