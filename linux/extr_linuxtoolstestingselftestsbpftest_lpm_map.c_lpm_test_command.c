#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lpm_mt_test_info {int iter; int cmd; int /*<<< orphan*/  map_fd; TYPE_1__* key; } ;
struct bpf_lpm_trie_key {int /*<<< orphan*/  data; int /*<<< orphan*/  prefixlen; } ;
typedef  int __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  prefixlen; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOMEM ; 
 int MAX_TEST_KEYS ; 
 struct bpf_lpm_trie_key* alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_map_delete_elem (int /*<<< orphan*/ ,struct bpf_lpm_trie_key*) ; 
 int bpf_map_get_next_key (int /*<<< orphan*/ ,struct bpf_lpm_trie_key*,struct bpf_lpm_trie_key*) ; 
 int bpf_map_lookup_elem (int /*<<< orphan*/ ,struct bpf_lpm_trie_key*,int*) ; 
 scalar_t__ bpf_map_update_elem (int /*<<< orphan*/ ,struct bpf_lpm_trie_key*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_exit (void*) ; 

__attribute__((used)) static void *lpm_test_command(void *arg)
{
	int i, j, ret, iter, key_size;
	struct lpm_mt_test_info *info = arg;
	struct bpf_lpm_trie_key *key_p;

	key_size = sizeof(struct bpf_lpm_trie_key) + sizeof(__u32);
	key_p = alloca(key_size);
	for (iter = 0; iter < info->iter; iter++)
		for (i = 0; i < MAX_TEST_KEYS; i++) {
			/* first half of iterations in forward order,
			 * and second half in backward order.
			 */
			j = (iter < (info->iter / 2)) ? i : MAX_TEST_KEYS - i - 1;
			key_p->prefixlen = info->key[j].prefixlen;
			memcpy(key_p->data, &info->key[j].data, sizeof(__u32));
			if (info->cmd == 0) {
				__u32 value = j;
				/* update must succeed */
				assert(bpf_map_update_elem(info->map_fd, key_p, &value, 0) == 0);
			} else if (info->cmd == 1) {
				ret = bpf_map_delete_elem(info->map_fd, key_p);
				assert(ret == 0 || errno == ENOENT);
			} else if (info->cmd == 2) {
				__u32 value;
				ret = bpf_map_lookup_elem(info->map_fd, key_p, &value);
				assert(ret == 0 || errno == ENOENT);
			} else {
				struct bpf_lpm_trie_key *next_key_p = alloca(key_size);
				ret = bpf_map_get_next_key(info->map_fd, key_p, next_key_p);
				assert(ret == 0 || errno == ENOENT || errno == ENOMEM);
			}
		}

	// Pass successful exit info back to the main thread
	pthread_exit((void *)info);
}