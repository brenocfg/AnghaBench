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
struct lpm_mt_test_info {int cmd; } ;
struct bpf_lpm_trie_key {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_NO_PREALLOC ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_LPM_TRIE ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,size_t,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  lpm_test_command ; 
 int /*<<< orphan*/  memcpy (struct lpm_mt_test_info*,struct lpm_mt_test_info*,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct lpm_mt_test_info*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  setup_lpm_mt_test_info (struct lpm_mt_test_info*,int) ; 

__attribute__((used)) static void test_lpm_multi_thread(void)
{
	struct lpm_mt_test_info info[4];
	size_t key_size, value_size;
	pthread_t thread_id[4];
	int i, map_fd;
	void *ret;

	/* create a trie */
	value_size = sizeof(__u32);
	key_size = sizeof(struct bpf_lpm_trie_key) + value_size;
	map_fd = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE, key_size, value_size,
				100, BPF_F_NO_PREALLOC);

	/* create 4 threads to test update, delete, lookup and get_next_key */
	setup_lpm_mt_test_info(&info[0], map_fd);
	for (i = 0; i < 4; i++) {
		if (i != 0)
			memcpy(&info[i], &info[0], sizeof(info[i]));
		info[i].cmd = i;
		assert(pthread_create(&thread_id[i], NULL, &lpm_test_command, &info[i]) == 0);
	}

	for (i = 0; i < 4; i++)
		assert(pthread_join(thread_id[i], &ret) == 0 && ret == (void *)&info[i]);

	close(map_fd);
}