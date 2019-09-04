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
struct rchan_buf {int finalized; int /*<<< orphan*/  kref; int /*<<< orphan*/  dentry; TYPE_2__* chan; int /*<<< orphan*/  wakeup_work; } ;
struct TYPE_4__ {TYPE_1__* cb; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* remove_buf_file ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  irq_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relay_remove_buf ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void relay_close_buf(struct rchan_buf *buf)
{
	buf->finalized = 1;
	irq_work_sync(&buf->wakeup_work);
	buf->chan->cb->remove_buf_file(buf->dentry);
	kref_put(&buf->kref, relay_remove_buf);
}