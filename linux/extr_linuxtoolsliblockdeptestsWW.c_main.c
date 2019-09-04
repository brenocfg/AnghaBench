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
typedef  int /*<<< orphan*/  pthread_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 

void main(void)
{
	pthread_rwlock_t a, b;

	pthread_rwlock_init(&a, NULL);
	pthread_rwlock_init(&b, NULL);

	pthread_rwlock_wrlock(&a);
	pthread_rwlock_rdlock(&b);
	pthread_rwlock_wrlock(&a);
}