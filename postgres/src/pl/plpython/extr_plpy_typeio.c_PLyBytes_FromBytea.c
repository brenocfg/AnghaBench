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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PLyDatumToOb ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetByteaPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyBytes_FromStringAndSize (char*,size_t) ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 size_t VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
PLyBytes_FromBytea(PLyDatumToOb *arg, Datum d)
{
	text	   *txt = DatumGetByteaPP(d);
	char	   *str = VARDATA_ANY(txt);
	size_t		size = VARSIZE_ANY_EXHDR(txt);

	return PyBytes_FromStringAndSize(str, size);
}