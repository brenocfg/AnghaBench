#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* array; } ;
struct signal_info {int /*<<< orphan*/  mutex; TYPE_6__ callbacks; scalar_t__ signalling; } ;
struct TYPE_8__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_2__ signal_handler_t ;
typedef  int /*<<< orphan*/  signal_callback_t ;
struct TYPE_7__ {int remove; int keep_ref; } ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int /*<<< orphan*/  da_erase (TYPE_6__,size_t) ; 
 struct signal_info* getsignal_locked (TYPE_2__*,char const*) ; 
 scalar_t__ os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t signal_get_callback_idx (struct signal_info*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  signal_handler_actually_destroy (TYPE_2__*) ; 

void signal_handler_disconnect(signal_handler_t *handler, const char *signal,
			       signal_callback_t callback, void *data)
{
	struct signal_info *sig = getsignal_locked(handler, signal);
	bool keep_ref = false;
	size_t idx;

	if (!sig)
		return;

	pthread_mutex_lock(&sig->mutex);

	idx = signal_get_callback_idx(sig, callback, data);
	if (idx != DARRAY_INVALID) {
		if (sig->signalling) {
			sig->callbacks.array[idx].remove = true;
		} else {
			keep_ref = sig->callbacks.array[idx].keep_ref;
			da_erase(sig->callbacks, idx);
		}
	}

	pthread_mutex_unlock(&sig->mutex);

	if (keep_ref && os_atomic_dec_long(&handler->refs) == 0) {
		signal_handler_actually_destroy(handler);
	}
}