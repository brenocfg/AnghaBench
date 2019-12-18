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
struct vm_area_struct {int /*<<< orphan*/  vm_file; struct rchan_buf* vm_private_data; } ;
struct rchan_buf {TYPE_2__* chan; } ;
struct TYPE_4__ {TYPE_1__* cb; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* buf_unmapped ) (struct rchan_buf*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rchan_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void relay_file_mmap_close(struct vm_area_struct *vma)
{
	struct rchan_buf *buf = vma->vm_private_data;
	buf->chan->cb->buf_unmapped(buf, vma->vm_file);
}