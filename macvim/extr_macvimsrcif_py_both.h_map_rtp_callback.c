#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * result; int /*<<< orphan*/  callable; } ;
typedef  TYPE_1__ map_rtp_data ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 

__attribute__((used)) static void
map_rtp_callback(char_u *path, void *_data)
{
    void	**data = (void **) _data;
    PyObject	*pathObject;
    map_rtp_data	*mr_data = *((map_rtp_data **) data);

    if (!(pathObject = PyString_FromString((char *)path)))
    {
	*data = NULL;
	return;
    }

    mr_data->result = PyObject_CallFunctionObjArgs(mr_data->callable,
						   pathObject, NULL);

    Py_DECREF(pathObject);

    if (!mr_data->result || mr_data->result != Py_None)
	*data = NULL;
    else
    {
	Py_DECREF(mr_data->result);
	mr_data->result = NULL;
    }
}