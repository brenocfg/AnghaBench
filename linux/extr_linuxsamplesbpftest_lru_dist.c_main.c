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
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  map_flags ;

/* Variables and functions */
 int BPF_F_NO_COMMON_LRU ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_LRU_HASH ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 int bpf_num_possible_cpus () ; 
 int /*<<< orphan*/  dist_key_counts ; 
 int /*<<< orphan*/  dist_keys ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int nr_cpus ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_keys (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  test_lru_loss0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_lru_loss1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_parallel_lru_dist (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  test_parallel_lru_loss (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	int map_flags[] = {0, BPF_F_NO_COMMON_LRU};
	const char *dist_file;
	int nr_tasks = 1;
	int lru_size;
	int f;

	if (argc < 4) {
		printf("Usage: %s <dist-file> <lru-size> <nr-tasks>\n",
		       argv[0]);
		return -1;
	}

	dist_file = argv[1];
	lru_size = atoi(argv[2]);
	nr_tasks = atoi(argv[3]);

	setbuf(stdout, NULL);

	assert(!setrlimit(RLIMIT_MEMLOCK, &r));

	srand(time(NULL));

	nr_cpus = bpf_num_possible_cpus();
	assert(nr_cpus != -1);
	printf("nr_cpus:%d\n\n", nr_cpus);

	nr_tasks = min(nr_tasks, nr_cpus);

	dist_key_counts = read_keys(dist_file, &dist_keys);
	if (!dist_key_counts) {
		printf("%s has no key\n", dist_file);
		return -1;
	}

	for (f = 0; f < sizeof(map_flags) / sizeof(*map_flags); f++) {
		test_lru_loss0(BPF_MAP_TYPE_LRU_HASH, map_flags[f]);
		test_lru_loss1(BPF_MAP_TYPE_LRU_HASH, map_flags[f]);
		test_parallel_lru_loss(BPF_MAP_TYPE_LRU_HASH, map_flags[f],
				       nr_tasks);
		test_parallel_lru_dist(BPF_MAP_TYPE_LRU_HASH, map_flags[f],
				       nr_tasks, lru_size);
		printf("\n");
	}

	free(dist_keys);

	return 0;
}