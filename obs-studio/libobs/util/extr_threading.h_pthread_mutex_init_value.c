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
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_MUTEX_INITIALIZER ; 

__attribute__((used)) static inline void pthread_mutex_init_value(pthread_mutex_t *mutex)
{
	pthread_mutex_t init_val = PTHREAD_MUTEX_INITIALIZER;
	if (!mutex)
		return;

	*mutex = init_val;
}