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

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rseq_register_current_thread () ; 
 scalar_t__ rseq_unregister_current_thread () ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  test_percpu_list () ; 
 int /*<<< orphan*/  test_percpu_spinlock () ; 

int main(int argc, char **argv)
{
	if (rseq_register_current_thread()) {
		fprintf(stderr, "Error: rseq_register_current_thread(...) failed(%d): %s\n",
			errno, strerror(errno));
		goto error;
	}
	printf("spinlock\n");
	test_percpu_spinlock();
	printf("percpu_list\n");
	test_percpu_list();
	if (rseq_unregister_current_thread()) {
		fprintf(stderr, "Error: rseq_unregister_current_thread(...) failed(%d): %s\n",
			errno, strerror(errno));
		goto error;
	}
	return 0;

error:
	return -1;
}