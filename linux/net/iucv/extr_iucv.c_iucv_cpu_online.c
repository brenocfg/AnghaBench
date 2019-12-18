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
 int /*<<< orphan*/  iucv_declare_cpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_path_table ; 

__attribute__((used)) static int iucv_cpu_online(unsigned int cpu)
{
	if (!iucv_path_table)
		return 0;
	iucv_declare_cpu(NULL);
	return 0;
}