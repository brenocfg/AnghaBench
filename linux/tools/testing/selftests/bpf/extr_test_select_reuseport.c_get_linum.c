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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*,char*,int,int /*<<< orphan*/ ) ; 
 int bpf_map_lookup_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  index_zero ; 
 int /*<<< orphan*/  linum_map ; 

__attribute__((used)) static __u32 get_linum(void)
{
	__u32 linum;
	int err;

	err = bpf_map_lookup_elem(linum_map, &index_zero, &linum);
	CHECK(err == -1, "lookup_elem(linum_map)", "err:%d errno:%d\n",
	      err, errno);

	return linum;
}