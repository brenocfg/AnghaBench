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
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  CHECK (int,char*,char*,int,int /*<<< orphan*/ ) ; 
 int bpf_map_update_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  index_zero ; 
 int /*<<< orphan*/  prepare_sk_fds (int,unsigned short,int) ; 
 int /*<<< orphan*/  tmp_index_ovr_map ; 

__attribute__((used)) static void setup_per_test(int type, unsigned short family, bool inany)
{
	int ovr = -1, err;

	prepare_sk_fds(type, family, inany);
	err = bpf_map_update_elem(tmp_index_ovr_map, &index_zero, &ovr,
				  BPF_ANY);
	CHECK(err == -1, "update_elem(tmp_index_ovr_map, 0, -1)",
	      "err:%d errno:%d\n", err, errno);
}