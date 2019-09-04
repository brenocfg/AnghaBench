#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int /*<<< orphan*/ * host_scribble; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; struct scsi_cmnd* tail; struct scsi_cmnd* head; } ;
typedef  TYPE_1__ ips_wait_queue_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 struct scsi_cmnd* ips_removeq_wait_head (TYPE_1__*) ; 

__attribute__((used)) static struct scsi_cmnd *ips_removeq_wait(ips_wait_queue_entry_t *queue,
					  struct scsi_cmnd *item)
{
	struct scsi_cmnd *p;

	METHOD_TRACE("ips_removeq_wait", 1);

	if (!item)
		return (NULL);

	if (item == queue->head) {
		return (ips_removeq_wait_head(queue));
	}

	p = queue->head;

	while ((p) && (item != (struct scsi_cmnd *) p->host_scribble))
		p = (struct scsi_cmnd *) p->host_scribble;

	if (p) {
		/* found a match */
		p->host_scribble = item->host_scribble;

		if (!item->host_scribble)
			queue->tail = p;

		item->host_scribble = NULL;
		queue->count--;

		return (item);
	}

	return (NULL);
}