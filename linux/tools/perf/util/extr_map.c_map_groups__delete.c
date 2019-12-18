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
struct map_groups {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct map_groups*) ; 
 int /*<<< orphan*/  map_groups__exit (struct map_groups*) ; 
 int /*<<< orphan*/  unwind__finish_access (struct map_groups*) ; 

void map_groups__delete(struct map_groups *mg)
{
	map_groups__exit(mg);
	unwind__finish_access(mg);
	free(mg);
}