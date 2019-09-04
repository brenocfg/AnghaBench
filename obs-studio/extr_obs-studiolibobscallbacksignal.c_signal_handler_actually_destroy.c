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
struct signal_info {struct signal_info* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  global_callbacks_mutex; int /*<<< orphan*/  global_callbacks; struct signal_info* first; } ;
typedef  TYPE_1__ signal_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_info_destroy (struct signal_info*) ; 

__attribute__((used)) static void signal_handler_actually_destroy(signal_handler_t *handler)
{
	struct signal_info *sig = handler->first;
	while (sig != NULL) {
		struct signal_info *next = sig->next;
		signal_info_destroy(sig);
		sig = next;
	}

	da_free(handler->global_callbacks);
	pthread_mutex_destroy(&handler->global_callbacks_mutex);
	pthread_mutex_destroy(&handler->mutex);
	bfree(handler);
}