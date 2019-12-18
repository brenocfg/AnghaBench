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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 scalar_t__ DEFAULT_RUNTIME ; 
 int DEFAULT_THREAD_COUNT ; 
 int MAX_THREADS ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int done ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 void* independent_thread (void*) ; 
 int /*<<< orphan*/  ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  localtime (scalar_t__*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void* (*) (void*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* shared_thread (void*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ time (scalar_t__*) ; 

int main(int argc, char **argv)
{
	int thread_count, i;
	time_t start, now, runtime;
	char buf[255];
	pthread_t pth[MAX_THREADS];
	int opt;
	void *tret;
	int ret = 0;
	void *(*thread)(void *) = shared_thread;

	thread_count = DEFAULT_THREAD_COUNT;
	runtime = DEFAULT_RUNTIME;

	/* Process arguments */
	while ((opt = getopt(argc, argv, "t:n:i")) != -1) {
		switch (opt) {
		case 't':
			runtime = atoi(optarg);
			break;
		case 'n':
			thread_count = atoi(optarg);
			break;
		case 'i':
			thread = independent_thread;
			printf("using independent threads\n");
			break;
		default:
			printf("Usage: %s [-t <secs>] [-n <numthreads>] [-i]\n", argv[0]);
			printf("	-t: time to run\n");
			printf("	-n: number of threads\n");
			printf("	-i: use independent threads\n");
			return -1;
		}
	}

	if (thread_count > MAX_THREADS)
		thread_count = MAX_THREADS;


	setbuf(stdout, NULL);

	start = time(0);
	strftime(buf, 255, "%a, %d %b %Y %T %z", localtime(&start));
	printf("%s\n", buf);
	printf("Testing consistency with %i threads for %ld seconds: ", thread_count, runtime);
	fflush(stdout);

	/* spawn */
	for (i = 0; i < thread_count; i++)
		pthread_create(&pth[i], 0, thread, 0);

	while (time(&now) < start + runtime) {
		sleep(1);
		if (done) {
			ret = 1;
			strftime(buf, 255, "%a, %d %b %Y %T %z", localtime(&now));
			printf("%s\n", buf);
			goto out;
		}
	}
	printf("[OK]\n");
	done = 1;

out:
	/* wait */
	for (i = 0; i < thread_count; i++)
		pthread_join(pth[i], &tret);

	/* die */
	if (ret)
		ksft_exit_fail();
	return ksft_exit_pass();
}