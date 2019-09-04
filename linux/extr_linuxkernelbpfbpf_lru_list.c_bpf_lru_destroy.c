#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  local_list; } ;
struct bpf_lru {TYPE_1__ common_lru; int /*<<< orphan*/  percpu_lru; scalar_t__ percpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 

void bpf_lru_destroy(struct bpf_lru *lru)
{
	if (lru->percpu)
		free_percpu(lru->percpu_lru);
	else
		free_percpu(lru->common_lru.local_list);
}