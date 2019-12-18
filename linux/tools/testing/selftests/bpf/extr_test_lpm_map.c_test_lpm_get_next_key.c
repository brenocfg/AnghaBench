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
struct bpf_lpm_trie_key {int prefixlen; int* data; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BPF_F_NO_PREALLOC ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_LPM_TRIE ; 
 scalar_t__ ENOENT ; 
 struct bpf_lpm_trie_key* alloca (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,size_t,int,int,int /*<<< orphan*/ ) ; 
 int bpf_map_get_next_key (int,struct bpf_lpm_trie_key*,struct bpf_lpm_trie_key*) ; 
 scalar_t__ bpf_map_update_elem (int,struct bpf_lpm_trie_key*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  memcpy (struct bpf_lpm_trie_key*,struct bpf_lpm_trie_key*,size_t) ; 
 int /*<<< orphan*/  memset (struct bpf_lpm_trie_key*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void test_lpm_get_next_key(void)
{
	struct bpf_lpm_trie_key *key_p, *next_key_p;
	size_t key_size;
	__u32 value = 0;
	int map_fd;

	key_size = sizeof(*key_p) + sizeof(__u32);
	key_p = alloca(key_size);
	next_key_p = alloca(key_size);

	map_fd = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE, key_size, sizeof(value),
				100, BPF_F_NO_PREALLOC);
	assert(map_fd >= 0);

	/* empty tree. get_next_key should return ENOENT */
	assert(bpf_map_get_next_key(map_fd, NULL, key_p) == -1 &&
	       errno == ENOENT);

	/* get and verify the first key, get the second one should fail. */
	key_p->prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", key_p->data);
	assert(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	memset(key_p, 0, key_size);
	assert(bpf_map_get_next_key(map_fd, NULL, key_p) == 0);
	assert(key_p->prefixlen == 16 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168);

	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       errno == ENOENT);

	/* no exact matching key should get the first one in post order. */
	key_p->prefixlen = 8;
	assert(bpf_map_get_next_key(map_fd, NULL, key_p) == 0);
	assert(key_p->prefixlen == 16 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168);

	/* add one more element (total two) */
	key_p->prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", key_p->data);
	assert(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	memset(key_p, 0, key_size);
	assert(bpf_map_get_next_key(map_fd, NULL, key_p) == 0);
	assert(key_p->prefixlen == 24 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168 && key_p->data[2] == 128);

	memset(next_key_p, 0, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 16 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       errno == ENOENT);

	/* Add one more element (total three) */
	key_p->prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", key_p->data);
	assert(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	memset(key_p, 0, key_size);
	assert(bpf_map_get_next_key(map_fd, NULL, key_p) == 0);
	assert(key_p->prefixlen == 24 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168 && key_p->data[2] == 0);

	memset(next_key_p, 0, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 128);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 16 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       errno == ENOENT);

	/* Add one more element (total four) */
	key_p->prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", key_p->data);
	assert(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	memset(key_p, 0, key_size);
	assert(bpf_map_get_next_key(map_fd, NULL, key_p) == 0);
	assert(key_p->prefixlen == 24 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168 && key_p->data[2] == 0);

	memset(next_key_p, 0, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 1);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 128);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 16 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       errno == ENOENT);

	/* Add one more element (total five) */
	key_p->prefixlen = 28;
	inet_pton(AF_INET, "192.168.1.128", key_p->data);
	assert(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	memset(key_p, 0, key_size);
	assert(bpf_map_get_next_key(map_fd, NULL, key_p) == 0);
	assert(key_p->prefixlen == 24 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168 && key_p->data[2] == 0);

	memset(next_key_p, 0, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 28 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 1 &&
	       next_key_p->data[3] == 128);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 1);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 128);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 16 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168);

	memcpy(key_p, next_key_p, key_size);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       errno == ENOENT);

	/* no exact matching key should return the first one in post order */
	key_p->prefixlen = 22;
	inet_pton(AF_INET, "192.168.1.0", key_p->data);
	assert(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	assert(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 0);

	close(map_fd);
}