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
struct thread_data {int dummy; } ;

/* Variables and functions */
 int THREADS ; 
 scalar_t__ go_away ; 
 int thread_create (int) ; 
 scalar_t__ thread_init (struct thread_data*) ; 
 struct thread_data* threads ; 

__attribute__((used)) static int threads_create(void)
{
	struct thread_data *td0 = &threads[0];
	int i, err = 0;

	go_away = 0;

	/* 0 is main thread */
	if (thread_init(td0))
		return -1;

	for (i = 1; !err && i < THREADS; i++)
		err = thread_create(i);

	return err;
}