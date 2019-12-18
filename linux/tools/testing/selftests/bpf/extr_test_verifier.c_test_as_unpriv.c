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
struct bpf_test {scalar_t__ prog_type; } ;

/* Variables and functions */
 scalar_t__ BPF_PROG_TYPE_CGROUP_SKB ; 
 scalar_t__ BPF_PROG_TYPE_SOCKET_FILTER ; 

__attribute__((used)) static bool test_as_unpriv(struct bpf_test *test)
{
	return !test->prog_type ||
	       test->prog_type == BPF_PROG_TYPE_SOCKET_FILTER ||
	       test->prog_type == BPF_PROG_TYPE_CGROUP_SKB;
}