#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int pthread_mutexattr_t ;
struct TYPE_4__ {int /*<<< orphan*/  srw; int /*<<< orphan*/  cs; } ;
struct TYPE_5__ {int use_cs; TYPE_1__ lock; } ;
typedef  TYPE_2__ pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeSRWLock (int /*<<< orphan*/ *) ; 
 int const PTHREAD_MUTEX_RECURSIVE ; 

int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr)
{
    mutex->use_cs = attr && (*attr & PTHREAD_MUTEX_RECURSIVE);
    if (mutex->use_cs) {
        InitializeCriticalSection(&mutex->lock.cs);
    } else {
        InitializeSRWLock(&mutex->lock.srw);
    }
    return 0;
}