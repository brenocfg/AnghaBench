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
struct TYPE_2__ {int num_cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_all_buffers () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  setup_all_buffers () ; 
 TYPE_1__ topo ; 

void re_initialize(void)
{
	free_all_buffers();
	setup_all_buffers();
	printf("turbostat: re-initialized with num_cpus %d\n", topo.num_cpus);
}