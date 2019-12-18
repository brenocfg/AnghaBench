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
 int /*<<< orphan*/  LOCK_UNLOCK_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void main(void)
{
	pthread_mutex_t a, b, c, d;

	pthread_mutex_init(&a, NULL);
	pthread_mutex_init(&b, NULL);
	pthread_mutex_init(&c, NULL);
	pthread_mutex_init(&d, NULL);

	LOCK_UNLOCK_2(a, b);
	LOCK_UNLOCK_2(b, c);
	LOCK_UNLOCK_2(c, d);
	LOCK_UNLOCK_2(d, a);

	pthread_mutex_destroy(&d);
	pthread_mutex_destroy(&c);
	pthread_mutex_destroy(&b);
	pthread_mutex_destroy(&a);
}