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
struct signal_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ signal_handler_t ;

/* Variables and functions */
 struct signal_info* getsignal (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct signal_info *getsignal_locked(signal_handler_t *handler,
						   const char *name)
{
	struct signal_info *sig;

	if (!handler)
		return NULL;

	pthread_mutex_lock(&handler->mutex);
	sig = getsignal(handler, name, NULL);
	pthread_mutex_unlock(&handler->mutex);

	return sig;
}