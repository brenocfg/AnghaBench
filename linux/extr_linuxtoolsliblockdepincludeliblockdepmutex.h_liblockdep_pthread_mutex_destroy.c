#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ liblockdep_pthread_mutex_t ;

/* Variables and functions */
 int pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int liblockdep_pthread_mutex_destroy(liblockdep_pthread_mutex_t *lock)
{
	return pthread_mutex_destroy(&lock->mutex);
}