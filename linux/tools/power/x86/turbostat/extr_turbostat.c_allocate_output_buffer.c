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
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * outp ; 
 int /*<<< orphan*/ * output_buffer ; 
 TYPE_1__ topo ; 

void allocate_output_buffer()
{
	output_buffer = calloc(1, (1 + topo.num_cpus) * 2048);
	outp = output_buffer;
	if (outp == NULL)
		err(-1, "calloc output buffer");
}