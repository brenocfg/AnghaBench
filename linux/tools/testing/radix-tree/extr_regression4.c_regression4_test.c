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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  mt_tree ; 
 int /*<<< orphan*/  obj0 ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printv (int,char*) ; 
 int /*<<< orphan*/  pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_fn ; 
 int /*<<< orphan*/  worker_barrier ; 
 int /*<<< orphan*/  writer_fn ; 

void regression4_test(void)
{
	pthread_t reader, writer;

	printv(1, "regression test 4 starting\n");

	radix_tree_insert(&mt_tree, 0, &obj0);
	pthread_barrier_init(&worker_barrier, NULL, 2);

	if (pthread_create(&reader, NULL, reader_fn, NULL) ||
	    pthread_create(&writer, NULL, writer_fn, NULL)) {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_join(reader, NULL) || pthread_join(writer, NULL)) {
		perror("pthread_join");
		exit(1);
	}

	printv(1, "regression test 4 passed\n");
}