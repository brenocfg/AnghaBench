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
struct dso {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dsos__add (struct dsos*,struct dso*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void dsos__add(struct dsos *dsos, struct dso *dso)
{
	down_write(&dsos->lock);
	__dsos__add(dsos, dso);
	up_write(&dsos->lock);
}