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
struct xsk_umem_info {int dummy; } ;
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 scalar_t__ BENCH_RXDROP ; 
 scalar_t__ BENCH_TXONLY ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  LC_ALL ; 
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int NUM_FRAMES ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_with_error (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gen_eth_frame (struct xsk_umem_info*,int) ; 
 int /*<<< orphan*/  get_nsecs () ; 
 int /*<<< orphan*/  int_exit ; 
 int /*<<< orphan*/  l2fwd_all () ; 
 void* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_socks ; 
 scalar_t__ opt_bench ; 
 int opt_mmap_flags ; 
 int opt_xsk_frame_size ; 
 int /*<<< orphan*/  parse_command_line (int,char**) ; 
 int /*<<< orphan*/  poller ; 
 int /*<<< orphan*/  prev_time ; 
 int /*<<< orphan*/  printf (char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_drop_all () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_only_all () ; 
 int /*<<< orphan*/  xsk_configure_socket (struct xsk_umem_info*) ; 
 struct xsk_umem_info* xsk_configure_umem (void*,int) ; 
 int /*<<< orphan*/ * xsks ; 

int main(int argc, char **argv)
{
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	struct xsk_umem_info *umem;
	pthread_t pt;
	void *bufs;
	int ret;

	parse_command_line(argc, argv);

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		fprintf(stderr, "ERROR: setrlimit(RLIMIT_MEMLOCK) \"%s\"\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Reserve memory for the umem. Use hugepages if unaligned chunk mode */
	bufs = mmap(NULL, NUM_FRAMES * opt_xsk_frame_size,
		    PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANONYMOUS | opt_mmap_flags, -1, 0);
	if (bufs == MAP_FAILED) {
		printf("ERROR: mmap failed\n");
		exit(EXIT_FAILURE);
	}
       /* Create sockets... */
	umem = xsk_configure_umem(bufs, NUM_FRAMES * opt_xsk_frame_size);
	xsks[num_socks++] = xsk_configure_socket(umem);

	if (opt_bench == BENCH_TXONLY) {
		int i;

		for (i = 0; i < NUM_FRAMES; i++)
			(void)gen_eth_frame(umem, i * opt_xsk_frame_size);
	}

	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);
	signal(SIGABRT, int_exit);

	setlocale(LC_ALL, "");

	ret = pthread_create(&pt, NULL, poller, NULL);
	if (ret)
		exit_with_error(ret);

	prev_time = get_nsecs();

	if (opt_bench == BENCH_RXDROP)
		rx_drop_all();
	else if (opt_bench == BENCH_TXONLY)
		tx_only_all();
	else
		l2fwd_all();

	return 0;
}