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
struct ipv_counts {int /*<<< orphan*/  v6; } ;
struct dummy_tracepoint_args {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 struct ipv_counts* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  btf_map ; 

__attribute__((used)) __attribute__((noinline))
static int test_long_fname_2(struct dummy_tracepoint_args *arg)
{
	struct ipv_counts *counts;
	int key = 0;

	if (!arg->sock)
		return 0;

	counts = bpf_map_lookup_elem(&btf_map, &key);
	if (!counts)
		return 0;

	counts->v6++;

	return 0;
}