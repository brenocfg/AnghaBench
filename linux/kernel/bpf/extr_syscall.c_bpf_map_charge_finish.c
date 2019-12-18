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
struct bpf_map_memory {int /*<<< orphan*/  user; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_uncharge_memlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_uid (int /*<<< orphan*/ ) ; 

void bpf_map_charge_finish(struct bpf_map_memory *mem)
{
	bpf_uncharge_memlock(mem->user, mem->pages);
	free_uid(mem->user);
}