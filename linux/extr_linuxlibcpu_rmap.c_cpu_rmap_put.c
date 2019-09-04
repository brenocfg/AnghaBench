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
struct cpu_rmap {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_rmap_release ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cpu_rmap_put(struct cpu_rmap *rmap)
{
	return kref_put(&rmap->refcount, cpu_rmap_release);
}