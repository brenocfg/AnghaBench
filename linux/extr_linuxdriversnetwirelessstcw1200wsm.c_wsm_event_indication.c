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
struct wsm_buf {int dummy; } ;
struct TYPE_2__ {void* data; void* id; } ;
struct cw1200_wsm_event {int /*<<< orphan*/  link; TYPE_1__ evt; } ;
struct cw1200_common {scalar_t__ mode; int /*<<< orphan*/  event_handler; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  event_queue_lock; int /*<<< orphan*/  event_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 void* WSM_GET32 (struct wsm_buf*) ; 
 int /*<<< orphan*/  kfree (struct cw1200_wsm_event*) ; 
 struct cw1200_wsm_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,void*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wsm_event_indication(struct cw1200_common *priv, struct wsm_buf *buf)
{
	int first;
	struct cw1200_wsm_event *event;

	if (priv->mode == NL80211_IFTYPE_UNSPECIFIED) {
		/* STA is stopped. */
		return 0;
	}

	event = kzalloc(sizeof(struct cw1200_wsm_event), GFP_KERNEL);
	if (!event)
		return -ENOMEM;

	event->evt.id = WSM_GET32(buf);
	event->evt.data = WSM_GET32(buf);

	pr_debug("[WSM] Event: %d(%d)\n",
		 event->evt.id, event->evt.data);

	spin_lock(&priv->event_queue_lock);
	first = list_empty(&priv->event_queue);
	list_add_tail(&event->link, &priv->event_queue);
	spin_unlock(&priv->event_queue_lock);

	if (first)
		queue_work(priv->workqueue, &priv->event_handler);

	return 0;

underflow:
	kfree(event);
	return -EINVAL;
}