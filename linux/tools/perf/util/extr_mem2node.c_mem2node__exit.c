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
struct mem2node {int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void mem2node__exit(struct mem2node *map)
{
	zfree(&map->entries);
}