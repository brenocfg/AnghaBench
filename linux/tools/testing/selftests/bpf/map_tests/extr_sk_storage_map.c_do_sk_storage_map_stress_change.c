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
 int /*<<< orphan*/  AF_INET6 ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int create_sk_storage_map () ; 
 int /*<<< orphan*/  delete_thread ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int nr_sk_threads ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  sk_storage_map ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop ; 
 int /*<<< orphan*/  update_thread ; 
 int /*<<< orphan*/  wait_for_threads_err () ; 

__attribute__((used)) static int do_sk_storage_map_stress_change(void)
{
	int i, sk_fd, map_fd = -1, err = 0, nr_threads_created = 0;
	pthread_t *sk_thread_ids;
	void *thread_ret;

	sk_thread_ids = malloc(sizeof(pthread_t) * nr_sk_threads);
	if (!sk_thread_ids) {
		fprintf(stderr, "malloc(sk_threads): NULL\n");
		return -ENOMEM;
	}

	sk_fd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sk_fd == -1) {
		err = -errno;
		goto done;
	}

	map_fd = create_sk_storage_map();
	WRITE_ONCE(sk_storage_map, map_fd);

	for (i = 0; i < nr_sk_threads; i++) {
		if (i & 0x1)
			err = pthread_create(&sk_thread_ids[i], NULL,
					     update_thread, &sk_fd);
		else
			err = pthread_create(&sk_thread_ids[i], NULL,
					     delete_thread, &sk_fd);
		if (err) {
			err = -errno;
			goto done;
		}
		nr_threads_created++;
	}

	wait_for_threads_err();

done:
	WRITE_ONCE(stop, 1);
	for (i = 0; i < nr_threads_created; i++) {
		pthread_join(sk_thread_ids[i], &thread_ret);
		if (IS_ERR(thread_ret) && !err) {
			err = PTR_ERR(thread_ret);
			fprintf(stderr, "threads#%u: err:%d\n", i, err);
		}
	}
	free(sk_thread_ids);

	if (sk_fd != -1)
		close(sk_fd);
	close(map_fd);

	return err;
}