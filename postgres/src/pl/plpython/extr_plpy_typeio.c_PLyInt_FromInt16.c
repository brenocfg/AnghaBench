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
 int /*<<< orphan*/  DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyInt_FromLong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
PLyInt_FromInt16(PLyDatumToOb *arg, Datum d)
{
	return PyInt_FromLong(DatumGetInt16(d));
}