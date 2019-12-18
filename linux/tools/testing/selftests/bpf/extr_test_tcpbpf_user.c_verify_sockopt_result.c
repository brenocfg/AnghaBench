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
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_EQ (int,int,char*) ; 
 int bpf_map_lookup_elem (int,int*,int*) ; 

int verify_sockopt_result(int sock_map_fd)
{
	__u32 key = 0;
	int res;
	int rv;

	/* check setsockopt for SAVE_SYN */
	rv = bpf_map_lookup_elem(sock_map_fd, &key, &res);
	EXPECT_EQ(0, rv, "d");
	EXPECT_EQ(0, res, "d");
	key = 1;
	/* check getsockopt for SAVED_SYN */
	rv = bpf_map_lookup_elem(sock_map_fd, &key, &res);
	EXPECT_EQ(0, rv, "d");
	EXPECT_EQ(1, res, "d");
	return 0;
err:
	return -1;
}