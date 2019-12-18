#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  visitproc ;
struct TYPE_3__ {int (* traverse ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  cur; } ;
typedef  TYPE_1__ IterObject ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
IterTraverse(IterObject *self, visitproc visit, void *arg)
{
    if (self->traverse != NULL)
	return self->traverse(self->cur, visit, arg);
    else
	return 0;
}