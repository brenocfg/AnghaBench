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
typedef  int wait_queue_head_t ;
struct TYPE_2__ {void* notifyresult_handle; void* notify_handle; } ;
struct uiscmdrsp {TYPE_1__ scsitaskmgmt; } ;
struct idr {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 void* simple_idr_get (struct idr*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_scsitaskmgmt_handles(struct idr *idrtable, spinlock_t *lock,
				       struct uiscmdrsp *cmdrsp,
				       wait_queue_head_t *event, int *result)
{
	/* specify the event that has to be triggered when this */
	/* cmd is complete */
	cmdrsp->scsitaskmgmt.notify_handle =
		simple_idr_get(idrtable, event, lock);
	cmdrsp->scsitaskmgmt.notifyresult_handle =
		simple_idr_get(idrtable, result, lock);
}