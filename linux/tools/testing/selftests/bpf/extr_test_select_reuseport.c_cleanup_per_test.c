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

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*,char*,int,int /*<<< orphan*/ ) ; 
 int REUSEPORT_ARRAY_SIZE ; 
 int bpf_map_delete_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epfd ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  index_zero ; 
 int /*<<< orphan*/  outer_map ; 
 int /*<<< orphan*/ * sk_fds ; 

__attribute__((used)) static void cleanup_per_test(void)
{
	int i, err;

	for (i = 0; i < REUSEPORT_ARRAY_SIZE; i++)
		close(sk_fds[i]);
	close(epfd);

	err = bpf_map_delete_elem(outer_map, &index_zero);
	CHECK(err == -1, "delete_elem(outer_map)",
	      "err:%d errno:%d\n", err, errno);
}