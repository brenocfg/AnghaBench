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
struct mid_q_entry {int mid_flags; int /*<<< orphan*/  qhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteMidQEntry (struct mid_q_entry*) ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 int MID_DELETED ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
cifs_delete_mid(struct mid_q_entry *mid)
{
	spin_lock(&GlobalMid_Lock);
	if (!(mid->mid_flags & MID_DELETED)) {
		list_del_init(&mid->qhead);
		mid->mid_flags |= MID_DELETED;
	}
	spin_unlock(&GlobalMid_Lock);

	DeleteMidQEntry(mid);
}