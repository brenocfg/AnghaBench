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
struct visorhba_devdata {int nextinsert; int /*<<< orphan*/  privlock; struct scsipending* pending; } ;
struct scsipending {char cmdtype; int /*<<< orphan*/  cmdrsp; int /*<<< orphan*/ * sent; } ;

/* Variables and functions */
 int EBUSY ; 
 int MAX_PENDING_REQUESTS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int add_scsipending_entry(struct visorhba_devdata *devdata,
				 char cmdtype, void *new)
{
	unsigned long flags;
	struct scsipending *entry;
	int insert_location;

	spin_lock_irqsave(&devdata->privlock, flags);
	insert_location = devdata->nextinsert;
	while (devdata->pending[insert_location].sent) {
		insert_location = (insert_location + 1) % MAX_PENDING_REQUESTS;
		if (insert_location == (int)devdata->nextinsert) {
			spin_unlock_irqrestore(&devdata->privlock, flags);
			return -EBUSY;
		}
	}

	entry = &devdata->pending[insert_location];
	memset(&entry->cmdrsp, 0, sizeof(entry->cmdrsp));
	entry->cmdtype = cmdtype;
	if (new)
		entry->sent = new;
	/* wants to send cmdrsp */
	else
		entry->sent = &entry->cmdrsp;
	devdata->nextinsert = (insert_location + 1) % MAX_PENDING_REQUESTS;
	spin_unlock_irqrestore(&devdata->privlock, flags);

	return insert_location;
}