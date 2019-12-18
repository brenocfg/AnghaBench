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

/* Variables and functions */
 int /*<<< orphan*/  RTLD_NEXT ; 
 scalar_t__ __init_state ; 
 void* dlsym (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ done ; 
 void* ll_pthread_mutex_destroy ; 
 void* ll_pthread_mutex_init ; 
 void* ll_pthread_mutex_lock ; 
 void* ll_pthread_mutex_trylock ; 
 void* ll_pthread_mutex_unlock ; 
 void* ll_pthread_rwlock_destroy ; 
 void* ll_pthread_rwlock_init ; 
 void* ll_pthread_rwlock_rdlock ; 
 void* ll_pthread_rwlock_tryrdlock ; 
 void* ll_pthread_rwlock_trywrlock ; 
 void* ll_pthread_rwlock_unlock ; 
 void* ll_pthread_rwlock_wrlock ; 
 scalar_t__ prepare ; 

__attribute__((used)) __attribute__((constructor)) static void init_preload(void)
{
	if (__init_state == done)
		return;

#ifndef __GLIBC__
	__init_state = prepare;

	ll_pthread_mutex_init = dlsym(RTLD_NEXT, "pthread_mutex_init");
	ll_pthread_mutex_lock = dlsym(RTLD_NEXT, "pthread_mutex_lock");
	ll_pthread_mutex_trylock = dlsym(RTLD_NEXT, "pthread_mutex_trylock");
	ll_pthread_mutex_unlock = dlsym(RTLD_NEXT, "pthread_mutex_unlock");
	ll_pthread_mutex_destroy = dlsym(RTLD_NEXT, "pthread_mutex_destroy");

	ll_pthread_rwlock_init = dlsym(RTLD_NEXT, "pthread_rwlock_init");
	ll_pthread_rwlock_destroy = dlsym(RTLD_NEXT, "pthread_rwlock_destroy");
	ll_pthread_rwlock_rdlock = dlsym(RTLD_NEXT, "pthread_rwlock_rdlock");
	ll_pthread_rwlock_tryrdlock = dlsym(RTLD_NEXT, "pthread_rwlock_tryrdlock");
	ll_pthread_rwlock_wrlock = dlsym(RTLD_NEXT, "pthread_rwlock_wrlock");
	ll_pthread_rwlock_trywrlock = dlsym(RTLD_NEXT, "pthread_rwlock_trywrlock");
	ll_pthread_rwlock_unlock = dlsym(RTLD_NEXT, "pthread_rwlock_unlock");
#endif

	__init_state = done;
}