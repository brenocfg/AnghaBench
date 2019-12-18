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
typedef  int /*<<< orphan*/  value ;
struct bpf_lpm_trie_key {int prefixlen; int /*<<< orphan*/  data; } ;
typedef  int __u64 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BPF_F_NO_PREALLOC ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_LPM_TRIE ; 
 scalar_t__ ENOENT ; 
 struct bpf_lpm_trie_key* alloca (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,size_t,int,int,int /*<<< orphan*/ ) ; 
 int bpf_map_delete_elem (int,struct bpf_lpm_trie_key*) ; 
 int bpf_map_lookup_elem (int,struct bpf_lpm_trie_key*,int*) ; 
 scalar_t__ bpf_map_update_elem (int,struct bpf_lpm_trie_key*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_lpm_delete(void)
{
	struct bpf_lpm_trie_key *key;
	size_t key_size;
	int map_fd;
	__u64 value;

	key_size = sizeof(*key) + sizeof(__u32);
	key = alloca(key_size);

	map_fd = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE,
				key_size, sizeof(value),
				100, BPF_F_NO_PREALLOC);
	assert(map_fd >= 0);

	/* Add nodes:
	 * 192.168.0.0/16   (1)
	 * 192.168.0.0/24   (2)
	 * 192.168.128.0/24 (3)
	 * 192.168.1.0/24   (4)
	 *
	 *         (1)
	 *        /   \
         *     (IM)    (3)
	 *    /   \
         *   (2)  (4)
	 */
	value = 1;
	key->prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", key->data);
	assert(bpf_map_update_elem(map_fd, key, &value, 0) == 0);

	value = 2;
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", key->data);
	assert(bpf_map_update_elem(map_fd, key, &value, 0) == 0);

	value = 3;
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", key->data);
	assert(bpf_map_update_elem(map_fd, key, &value, 0) == 0);

	value = 4;
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", key->data);
	assert(bpf_map_update_elem(map_fd, key, &value, 0) == 0);

	/* remove non-existent node */
	key->prefixlen = 32;
	inet_pton(AF_INET, "10.0.0.1", key->data);
	assert(bpf_map_lookup_elem(map_fd, key, &value) == -1 &&
		errno == ENOENT);

	key->prefixlen = 30; // unused prefix so far
	inet_pton(AF_INET, "192.255.0.0", key->data);
	assert(bpf_map_delete_elem(map_fd, key) == -1 &&
		errno == ENOENT);

	key->prefixlen = 16; // same prefix as the root node
	inet_pton(AF_INET, "192.255.0.0", key->data);
	assert(bpf_map_delete_elem(map_fd, key) == -1 &&
		errno == ENOENT);

	/* assert initial lookup */
	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.0.1", key->data);
	assert(bpf_map_lookup_elem(map_fd, key, &value) == 0);
	assert(value == 2);

	/* remove leaf node */
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", key->data);
	assert(bpf_map_delete_elem(map_fd, key) == 0);

	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.0.1", key->data);
	assert(bpf_map_lookup_elem(map_fd, key, &value) == 0);
	assert(value == 1);

	/* remove leaf (and intermediary) node */
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", key->data);
	assert(bpf_map_delete_elem(map_fd, key) == 0);

	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.1.1", key->data);
	assert(bpf_map_lookup_elem(map_fd, key, &value) == 0);
	assert(value == 1);

	/* remove root node */
	key->prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", key->data);
	assert(bpf_map_delete_elem(map_fd, key) == 0);

	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.128.1", key->data);
	assert(bpf_map_lookup_elem(map_fd, key, &value) == 0);
	assert(value == 3);

	/* remove last node */
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", key->data);
	assert(bpf_map_delete_elem(map_fd, key) == 0);

	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.128.1", key->data);
	assert(bpf_map_lookup_elem(map_fd, key, &value) == -1 &&
		errno == ENOENT);

	close(map_fd);
}