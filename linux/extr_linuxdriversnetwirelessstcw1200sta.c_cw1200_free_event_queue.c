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
struct cw1200_common {int /*<<< orphan*/  event_queue_lock; int /*<<< orphan*/  event_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cw1200_free_event_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void cw1200_free_event_queue(struct cw1200_common *priv)
{
	LIST_HEAD(list);

	spin_lock(&priv->event_queue_lock);
	list_splice_init(&priv->event_queue, &list);
	spin_unlock(&priv->event_queue_lock);

	__cw1200_free_event_queue(&list);
}