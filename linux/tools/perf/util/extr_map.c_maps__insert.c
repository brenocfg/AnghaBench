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
struct maps {int /*<<< orphan*/  lock; } ;
struct map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __maps__insert (struct maps*,struct map*) ; 
 int /*<<< orphan*/  __maps__insert_name (struct maps*,struct map*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void maps__insert(struct maps *maps, struct map *map)
{
	down_write(&maps->lock);
	__maps__insert(maps, map);
	__maps__insert_name(maps, map);
	up_write(&maps->lock);
}