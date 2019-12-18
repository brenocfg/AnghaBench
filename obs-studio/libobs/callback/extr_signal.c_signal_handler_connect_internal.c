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
struct signal_info {int /*<<< orphan*/  mutex; int /*<<< orphan*/  callbacks; } ;
struct signal_callback {void* member_1; int member_2; int member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  refs; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ signal_handler_t ;
typedef  int /*<<< orphan*/  signal_callback_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct signal_callback*) ; 
 struct signal_info* getsignal (TYPE_1__*,char const*,struct signal_info**) ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t signal_get_callback_idx (struct signal_info*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void signal_handler_connect_internal(signal_handler_t *handler,
					    const char *signal,
					    signal_callback_t callback,
					    void *data, bool keep_ref)
{
	struct signal_info *sig, *last;
	struct signal_callback cb_data = {callback, data, false, keep_ref};
	size_t idx;

	if (!handler)
		return;

	pthread_mutex_lock(&handler->mutex);
	sig = getsignal(handler, signal, &last);
	pthread_mutex_unlock(&handler->mutex);

	if (!sig) {
		blog(LOG_WARNING,
		     "signal_handler_connect: "
		     "signal '%s' not found",
		     signal);
		return;
	}

	/* -------------- */

	pthread_mutex_lock(&sig->mutex);

	if (keep_ref)
		os_atomic_inc_long(&handler->refs);

	idx = signal_get_callback_idx(sig, callback, data);
	if (keep_ref || idx == DARRAY_INVALID)
		da_push_back(sig->callbacks, &cb_data);

	pthread_mutex_unlock(&sig->mutex);
}