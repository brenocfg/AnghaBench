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
struct signal_handler {int refs; int /*<<< orphan*/  mutex; int /*<<< orphan*/  global_callbacks_mutex; int /*<<< orphan*/ * first; } ;
typedef  struct signal_handler signal_handler_t ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  bfree (struct signal_handler*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 struct signal_handler* bzalloc (int) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

signal_handler_t *signal_handler_create(void)
{
	struct signal_handler *handler = bzalloc(sizeof(struct signal_handler));
	handler->first = NULL;
	handler->refs = 1;

	pthread_mutexattr_t attr;
	if (pthread_mutexattr_init(&attr) != 0)
		return NULL;
	if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
		return NULL;

	if (pthread_mutex_init(&handler->mutex, NULL) != 0) {
		blog(LOG_ERROR, "Couldn't create signal handler mutex!");
		bfree(handler);
		return NULL;
	}
	if (pthread_mutex_init(&handler->global_callbacks_mutex, &attr) != 0) {
		blog(LOG_ERROR, "Couldn't create signal handler global "
				"callbacks mutex!");
		pthread_mutex_destroy(&handler->mutex);
		bfree(handler);
		return NULL;
	}

	return handler;
}