#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  expires; } ;
struct TYPE_7__ {struct TYPE_7__* name; void* data; int /*<<< orphan*/  cb; TYPE_2__ t; scalar_t__ scheduled; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ dwc_timer_t ;
typedef  int /*<<< orphan*/  dwc_timer_callback_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_ALLOC () ; 
 TYPE_1__* DWC_STRDUP (char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  timer_callback ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

dwc_timer_t *DWC_TIMER_ALLOC(char *name, dwc_timer_callback_t cb, void *data)
{
	dwc_timer_t *t = DWC_ALLOC(sizeof(*t));

	if (!t) {
		DWC_ERROR("Cannot allocate memory for timer");
		return NULL;
	}

	t->name = DWC_STRDUP(name);
	if (!t->name) {
		DWC_ERROR("Cannot allocate memory for timer->name");
		goto no_name;
	}

#if (defined(DWC_LINUX) && defined(CONFIG_DEBUG_SPINLOCK))
	DWC_SPINLOCK_ALLOC_LINUX_DEBUG(t->lock);
#else
	t->lock = DWC_SPINLOCK_ALLOC();
#endif
	if (!t->lock) {
		DWC_ERROR("Cannot allocate memory for lock");
		goto no_lock;
	}

	t->scheduled = 0;
	t->t.expires = jiffies;
	timer_setup(&t->t, timer_callback, 0);

	t->cb = cb;
	t->data = data;

	return t;

 no_lock:
	DWC_FREE(t->name);
 no_name:
	DWC_FREE(t);
	return NULL;
}