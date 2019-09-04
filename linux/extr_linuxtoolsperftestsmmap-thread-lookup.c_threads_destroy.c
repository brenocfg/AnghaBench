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
struct thread_data {int /*<<< orphan*/  pt; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int THREADS ; 
 int go_away ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_size ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct thread_data* threads ; 

__attribute__((used)) static int threads_destroy(void)
{
	struct thread_data *td0 = &threads[0];
	int i, err = 0;

	/* cleanup the main thread */
	munmap(td0->map, page_size);

	go_away = 1;

	for (i = 1; !err && i < THREADS; i++)
		err = pthread_join(threads[i].pt, NULL);

	return err;
}