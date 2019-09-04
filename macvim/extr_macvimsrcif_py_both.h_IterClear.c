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
struct TYPE_3__ {int (* clear ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  cur; } ;
typedef  TYPE_1__ IterObject ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
IterClear(IterObject *self)
{
    if (self->clear != NULL)
	return self->clear(&self->cur);
    else
	return 0;
}