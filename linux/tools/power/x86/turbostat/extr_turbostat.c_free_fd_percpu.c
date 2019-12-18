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
struct TYPE_2__ {int max_cpu_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__* fd_percpu ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 TYPE_1__ topo ; 

void free_fd_percpu(void)
{
	int i;

	for (i = 0; i < topo.max_cpu_num + 1; ++i) {
		if (fd_percpu[i] != 0)
			close(fd_percpu[i]);
	}

	free(fd_percpu);
}