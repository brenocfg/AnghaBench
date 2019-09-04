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
struct dsos {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsos__purge (struct dsos*) ; 
 int /*<<< orphan*/  exit_rwsem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsos__exit(struct dsos *dsos)
{
	dsos__purge(dsos);
	exit_rwsem(&dsos->lock);
}