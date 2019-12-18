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

/* Variables and functions */
 int /*<<< orphan*/  __maps__purge (struct maps*) ; 
 int /*<<< orphan*/  __maps__purge_names (struct maps*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void maps__exit(struct maps *maps)
{
	down_write(&maps->lock);
	__maps__purge(maps);
	__maps__purge_names(maps);
	up_write(&maps->lock);
}