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
struct TYPE_2__ {int max_entries; } ;
struct bpf_array {int /*<<< orphan*/ * pptrs; TYPE_1__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bpf_array_free_percpu(struct bpf_array *array)
{
	int i;

	for (i = 0; i < array->map.max_entries; i++) {
		free_percpu(array->pptrs[i]);
		cond_resched();
	}
}