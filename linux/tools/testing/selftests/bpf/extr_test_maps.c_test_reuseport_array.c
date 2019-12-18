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
typedef  scalar_t__ __u64 ;
typedef  size_t __u32 ;
typedef  int __s64 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  BPF_EXIST ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_REUSEPORT_SOCKARRAY ; 
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int /*<<< orphan*/  CHECK (int,char*,char*,int,int,...) ; 
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  ENOTSUPP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 size_t REUSEPORT_FD_IDX (int,size_t) ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int SOCK_STREAM ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,size_t const,int /*<<< orphan*/ ) ; 
 int bpf_map_delete_elem (int,size_t const*) ; 
 int bpf_map_lookup_elem (int,size_t const*,scalar_t__*) ; 
 int bpf_map_update_elem (int,size_t const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  prepare_reuseport_grp (int,int,int,int*,scalar_t__*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_reuseport_array(void)
{
#define REUSEPORT_FD_IDX(err, last) ({ (err) ? last : !last; })

	const __u32 array_size = 4, index0 = 0, index3 = 3;
	int types[2] = { SOCK_STREAM, SOCK_DGRAM }, type;
	__u64 grpa_cookies[2], sk_cookie, map_cookie;
	__s64 grpa_fds64[2] = { -1, -1 }, fd64 = -1;
	const __u32 bad_index = array_size;
	int map_fd, err, t, f;
	__u32 fds_idx = 0;
	int fd;

	map_fd = bpf_create_map(BPF_MAP_TYPE_REUSEPORT_SOCKARRAY,
				sizeof(__u32), sizeof(__u64), array_size, 0);
	CHECK(map_fd == -1, "reuseport array create",
	      "map_fd:%d, errno:%d\n", map_fd, errno);

	/* Test lookup/update/delete with invalid index */
	err = bpf_map_delete_elem(map_fd, &bad_index);
	CHECK(err != -1 || errno != E2BIG, "reuseport array del >=max_entries",
	      "err:%d errno:%d\n", err, errno);

	err = bpf_map_update_elem(map_fd, &bad_index, &fd64, BPF_ANY);
	CHECK(err != -1 || errno != E2BIG,
	      "reuseport array update >=max_entries",
	      "err:%d errno:%d\n", err, errno);

	err = bpf_map_lookup_elem(map_fd, &bad_index, &map_cookie);
	CHECK(err != -1 || errno != ENOENT,
	      "reuseport array update >=max_entries",
	      "err:%d errno:%d\n", err, errno);

	/* Test lookup/delete non existence elem */
	err = bpf_map_lookup_elem(map_fd, &index3, &map_cookie);
	CHECK(err != -1 || errno != ENOENT,
	      "reuseport array lookup not-exist elem",
	      "err:%d errno:%d\n", err, errno);
	err = bpf_map_delete_elem(map_fd, &index3);
	CHECK(err != -1 || errno != ENOENT,
	      "reuseport array del not-exist elem",
	      "err:%d errno:%d\n", err, errno);

	for (t = 0; t < ARRAY_SIZE(types); t++) {
		type = types[t];

		prepare_reuseport_grp(type, map_fd, sizeof(__u64), grpa_fds64,
				      grpa_cookies, ARRAY_SIZE(grpa_fds64));

		/* Test BPF_* update flags */
		/* BPF_EXIST failure case */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_EXIST);
		CHECK(err != -1 || errno != ENOENT,
		      "reuseport array update empty elem BPF_EXIST",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, errno);
		fds_idx = REUSEPORT_FD_IDX(err, fds_idx);

		/* BPF_NOEXIST success case */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_NOEXIST);
		CHECK(err == -1,
		      "reuseport array update empty elem BPF_NOEXIST",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, errno);
		fds_idx = REUSEPORT_FD_IDX(err, fds_idx);

		/* BPF_EXIST success case. */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_EXIST);
		CHECK(err == -1,
		      "reuseport array update same elem BPF_EXIST",
		      "sock_type:%d err:%d errno:%d\n", type, err, errno);
		fds_idx = REUSEPORT_FD_IDX(err, fds_idx);

		/* BPF_NOEXIST failure case */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_NOEXIST);
		CHECK(err != -1 || errno != EEXIST,
		      "reuseport array update non-empty elem BPF_NOEXIST",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, errno);
		fds_idx = REUSEPORT_FD_IDX(err, fds_idx);

		/* BPF_ANY case (always succeed) */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_ANY);
		CHECK(err == -1,
		      "reuseport array update same sk with BPF_ANY",
		      "sock_type:%d err:%d errno:%d\n", type, err, errno);

		fd64 = grpa_fds64[fds_idx];
		sk_cookie = grpa_cookies[fds_idx];

		/* The same sk cannot be added to reuseport_array twice */
		err = bpf_map_update_elem(map_fd, &index3, &fd64, BPF_ANY);
		CHECK(err != -1 || errno != EBUSY,
		      "reuseport array update same sk with same index",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, errno);

		err = bpf_map_update_elem(map_fd, &index0, &fd64, BPF_ANY);
		CHECK(err != -1 || errno != EBUSY,
		      "reuseport array update same sk with different index",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, errno);

		/* Test delete elem */
		err = bpf_map_delete_elem(map_fd, &index3);
		CHECK(err == -1, "reuseport array delete sk",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, errno);

		/* Add it back with BPF_NOEXIST */
		err = bpf_map_update_elem(map_fd, &index3, &fd64, BPF_NOEXIST);
		CHECK(err == -1,
		      "reuseport array re-add with BPF_NOEXIST after del",
		      "sock_type:%d err:%d errno:%d\n", type, err, errno);

		/* Test cookie */
		err = bpf_map_lookup_elem(map_fd, &index3, &map_cookie);
		CHECK(err == -1 || sk_cookie != map_cookie,
		      "reuseport array lookup re-added sk",
		      "sock_type:%d err:%d errno:%d sk_cookie:0x%llx map_cookie:0x%llxn",
		      type, err, errno, sk_cookie, map_cookie);

		/* Test elem removed by close() */
		for (f = 0; f < ARRAY_SIZE(grpa_fds64); f++)
			close(grpa_fds64[f]);
		err = bpf_map_lookup_elem(map_fd, &index3, &map_cookie);
		CHECK(err != -1 || errno != ENOENT,
		      "reuseport array lookup after close()",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, errno);
	}

	/* Test SOCK_RAW */
	fd64 = socket(AF_INET6, SOCK_RAW, IPPROTO_UDP);
	CHECK(fd64 == -1, "socket(SOCK_RAW)", "err:%d errno:%d\n",
	      err, errno);
	err = bpf_map_update_elem(map_fd, &index3, &fd64, BPF_NOEXIST);
	CHECK(err != -1 || errno != ENOTSUPP, "reuseport array update SOCK_RAW",
	      "err:%d errno:%d\n", err, errno);
	close(fd64);

	/* Close the 64 bit value map */
	close(map_fd);

	/* Test 32 bit fd */
	map_fd = bpf_create_map(BPF_MAP_TYPE_REUSEPORT_SOCKARRAY,
				sizeof(__u32), sizeof(__u32), array_size, 0);
	CHECK(map_fd == -1, "reuseport array create",
	      "map_fd:%d, errno:%d\n", map_fd, errno);
	prepare_reuseport_grp(SOCK_STREAM, map_fd, sizeof(__u32), &fd64,
			      &sk_cookie, 1);
	fd = fd64;
	err = bpf_map_update_elem(map_fd, &index3, &fd, BPF_NOEXIST);
	CHECK(err == -1, "reuseport array update 32 bit fd",
	      "err:%d errno:%d\n", err, errno);
	err = bpf_map_lookup_elem(map_fd, &index3, &map_cookie);
	CHECK(err != -1 || errno != ENOSPC,
	      "reuseport array lookup 32 bit fd",
	      "err:%d errno:%d\n", err, errno);
	close(fd);
	close(map_fd);
}