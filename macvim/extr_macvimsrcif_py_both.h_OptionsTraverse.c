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
struct TYPE_3__ {int /*<<< orphan*/  fromObj; } ;
typedef  TYPE_1__ OptionsObject ;

/* Variables and functions */
 int /*<<< orphan*/  Py_VISIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
OptionsTraverse(OptionsObject *self, visitproc visit, void *arg)
{
    Py_VISIT(self->fromObj);
    return 0;
}