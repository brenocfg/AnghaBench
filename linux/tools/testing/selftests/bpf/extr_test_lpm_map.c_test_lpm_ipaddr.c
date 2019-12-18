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
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  BPF_F_NO_PREALLOC ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_LPM_TRIE ; 
 scalar_t__ ENOENT ; 
 struct bpf_lpm_trie_key* alloca (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,size_t,int,int,int /*<<< orphan*/ ) ; 
 int bpf_map_lookup_elem (int,struct bpf_lpm_trie_key*,int*) ; 
 scalar_t__ bpf_map_update_elem (int,struct bpf_lpm_trie_key*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_lpm_ipaddr(void)
{
	struct bpf_lpm_trie_key *key_ipv4;
	struct bpf_lpm_trie_key *key_ipv6;
	size_t key_size_ipv4;
	size_t key_size_ipv6;
	int map_fd_ipv4;
	int map_fd_ipv6;
	__u64 value;

	key_size_ipv4 = sizeof(*key_ipv4) + sizeof(__u32);
	key_size_ipv6 = sizeof(*key_ipv6) + sizeof(__u32) * 4;
	key_ipv4 = alloca(key_size_ipv4);
	key_ipv6 = alloca(key_size_ipv6);

	map_fd_ipv4 = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE,
				     key_size_ipv4, sizeof(value),
				     100, BPF_F_NO_PREALLOC);
	assert(map_fd_ipv4 >= 0);

	map_fd_ipv6 = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE,
				     key_size_ipv6, sizeof(value),
				     100, BPF_F_NO_PREALLOC);
	assert(map_fd_ipv6 >= 0);

	/* Fill data some IPv4 and IPv6 address ranges */
	value = 1;
	key_ipv4->prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", key_ipv4->data);
	assert(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 2;
	key_ipv4->prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", key_ipv4->data);
	assert(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 3;
	key_ipv4->prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", key_ipv4->data);
	assert(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 5;
	key_ipv4->prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", key_ipv4->data);
	assert(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 4;
	key_ipv4->prefixlen = 23;
	inet_pton(AF_INET, "192.168.0.0", key_ipv4->data);
	assert(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 0xdeadbeef;
	key_ipv6->prefixlen = 64;
	inet_pton(AF_INET6, "2a00:1450:4001:814::200e", key_ipv6->data);
	assert(bpf_map_update_elem(map_fd_ipv6, key_ipv6, &value, 0) == 0);

	/* Set tprefixlen to maximum for lookups */
	key_ipv4->prefixlen = 32;
	key_ipv6->prefixlen = 128;

	/* Test some lookups that should come back with a value */
	inet_pton(AF_INET, "192.168.128.23", key_ipv4->data);
	assert(bpf_map_lookup_elem(map_fd_ipv4, key_ipv4, &value) == 0);
	assert(value == 3);

	inet_pton(AF_INET, "192.168.0.1", key_ipv4->data);
	assert(bpf_map_lookup_elem(map_fd_ipv4, key_ipv4, &value) == 0);
	assert(value == 2);

	inet_pton(AF_INET6, "2a00:1450:4001:814::", key_ipv6->data);
	assert(bpf_map_lookup_elem(map_fd_ipv6, key_ipv6, &value) == 0);
	assert(value == 0xdeadbeef);

	inet_pton(AF_INET6, "2a00:1450:4001:814::1", key_ipv6->data);
	assert(bpf_map_lookup_elem(map_fd_ipv6, key_ipv6, &value) == 0);
	assert(value == 0xdeadbeef);

	/* Test some lookups that should not match any entry */
	inet_pton(AF_INET, "10.0.0.1", key_ipv4->data);
	assert(bpf_map_lookup_elem(map_fd_ipv4, key_ipv4, &value) == -1 &&
	       errno == ENOENT);

	inet_pton(AF_INET, "11.11.11.11", key_ipv4->data);
	assert(bpf_map_lookup_elem(map_fd_ipv4, key_ipv4, &value) == -1 &&
	       errno == ENOENT);

	inet_pton(AF_INET6, "2a00:ffff::", key_ipv6->data);
	assert(bpf_map_lookup_elem(map_fd_ipv6, key_ipv6, &value) == -1 &&
	       errno == ENOENT);

	close(map_fd_ipv4);
	close(map_fd_ipv6);
}