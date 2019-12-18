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
struct padata_instance {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __padata_stop (struct padata_instance*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void padata_stop(struct padata_instance *pinst)
{
	mutex_lock(&pinst->lock);
	__padata_stop(pinst);
	mutex_unlock(&pinst->lock);
}