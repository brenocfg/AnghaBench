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
typedef  int /*<<< orphan*/  PLyDatumToOb ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyFloat_FromDouble (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
PLyFloat_FromFloat8(PLyDatumToOb *arg, Datum d)
{
	return PyFloat_FromDouble(DatumGetFloat8(d));
}