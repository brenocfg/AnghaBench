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
struct TYPE_3__ {int /*<<< orphan*/  ao; } ;
typedef  TYPE_1__ PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
array_iter_base_dealloc(PyArrayIterObject *it)
{
    Py_XDECREF(it->ao);
}