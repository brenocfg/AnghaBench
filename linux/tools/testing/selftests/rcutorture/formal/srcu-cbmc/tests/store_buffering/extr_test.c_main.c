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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 scalar_t__ __unbuffered_tpr_x ; 
 scalar_t__ __unbuffered_tpr_y ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_process_reader ; 
 int /*<<< orphan*/  thread_update ; 

int main(int argc, char *argv[])
{
	pthread_t tu;
	pthread_t tpr;

	if (pthread_create(&tu, NULL, thread_update, NULL))
		abort();
	if (pthread_create(&tpr, NULL, thread_process_reader, NULL))
		abort();
	if (pthread_join(tu, NULL))
		abort();
	if (pthread_join(tpr, NULL))
		abort();
	assert(__unbuffered_tpr_y != 0 || __unbuffered_tpr_x != 0);

#ifdef ASSERT_END
	assert(0);
#endif

	return 0;
}