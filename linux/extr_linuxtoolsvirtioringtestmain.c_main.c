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
 long INT_MAX ; 
 int /*<<< orphan*/  alloc_ring () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ batch ; 
 scalar_t__ callfd ; 
 int do_exit ; 
 int do_relax ; 
 int do_sleep ; 
 scalar_t__ eventfd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt_long (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  help () ; 
 scalar_t__ kickfd ; 
 int /*<<< orphan*/  longopts ; 
 scalar_t__ max_outstanding ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  optstring ; 
 long param ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int ring_size ; 
 long runcycles ; 
 int /*<<< orphan*/  smp_acquire () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_release () ; 
 int /*<<< orphan*/  start_guest ; 
 int /*<<< orphan*/  start_host ; 
 void* strtol (char*,char**,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	int ret;
	pthread_t host, guest;
	void *tret;
	char *host_arg = NULL;
	char *guest_arg = NULL;
	char *endptr;
	long int c;

	kickfd = eventfd(0, 0);
	assert(kickfd >= 0);
	callfd = eventfd(0, 0);
	assert(callfd >= 0);

	for (;;) {
		int o = getopt_long(argc, argv, optstring, longopts, NULL);
		switch (o) {
		case -1:
			goto done;
		case '?':
			help();
			exit(2);
		case 'H':
			host_arg = optarg;
			break;
		case 'G':
			guest_arg = optarg;
			break;
		case 'R':
			ring_size = strtol(optarg, &endptr, 0);
			assert(ring_size && !(ring_size & (ring_size - 1)));
			assert(!*endptr);
			break;
		case 'C':
			c = strtol(optarg, &endptr, 0);
			assert(!*endptr);
			assert(c > 0 && c < INT_MAX);
			runcycles = c;
			break;
		case 'o':
			c = strtol(optarg, &endptr, 0);
			assert(!*endptr);
			assert(c > 0 && c < INT_MAX);
			max_outstanding = c;
			break;
		case 'p':
			c = strtol(optarg, &endptr, 0);
			assert(!*endptr);
			assert(c > 0 && c < INT_MAX);
			param = c;
			break;
		case 'b':
			c = strtol(optarg, &endptr, 0);
			assert(!*endptr);
			assert(c > 0 && c < INT_MAX);
			batch = c;
			break;
		case 's':
			do_sleep = true;
			break;
		case 'x':
			do_relax = true;
			break;
		case 'e':
			do_exit = true;
			break;
		default:
			help();
			exit(4);
			break;
		}
	}

	/* does nothing here, used to make sure all smp APIs compile */
	smp_acquire();
	smp_release();
	smp_mb();
done:

	if (batch > max_outstanding)
		batch = max_outstanding;

	if (optind < argc) {
		help();
		exit(4);
	}
	alloc_ring();

	ret = pthread_create(&host, NULL, start_host, host_arg);
	assert(!ret);
	ret = pthread_create(&guest, NULL, start_guest, guest_arg);
	assert(!ret);

	ret = pthread_join(guest, &tret);
	assert(!ret);
	ret = pthread_join(host, &tret);
	assert(!ret);
	return 0;
}