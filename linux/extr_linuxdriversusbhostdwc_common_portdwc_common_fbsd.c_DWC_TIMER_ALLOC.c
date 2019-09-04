#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* name; void* data; int /*<<< orphan*/  cb; int /*<<< orphan*/  lock; int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ dwc_timer_t ;
typedef  int /*<<< orphan*/  dwc_timer_callback_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_ALLOC () ; 
 TYPE_1__* DWC_STRDUP (char*) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 

dwc_timer_t *DWC_TIMER_ALLOC(char *name, dwc_timer_callback_t cb, void *data)
{
	dwc_timer_t *t = DWC_ALLOC(sizeof(*t));

	if (!t) {
		DWC_ERROR("Cannot allocate memory for timer");
		return NULL;
	}

	callout_init(&t->t, 1);

	t->name = DWC_STRDUP(name);
	if (!t->name) {
		DWC_ERROR("Cannot allocate memory for timer->name");
		goto no_name;
	}

	t->lock = DWC_SPINLOCK_ALLOC();
	if (!t->lock) {
		DWC_ERROR("Cannot allocate memory for lock");
		goto no_lock;
	}

	t->cb = cb;
	t->data = data;

	return t;

 no_lock:
	DWC_FREE(t->name);
 no_name:
	DWC_FREE(t);

	return NULL;
}