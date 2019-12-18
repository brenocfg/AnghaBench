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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * execute_real_backward (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/ * execute_real_forward (int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static PyObject *
execute_real(PyObject *a1, int is_forward, double fct)
{
    return is_forward ? execute_real_forward(a1, fct)
                      : execute_real_backward(a1, fct);
}