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
typedef  int npy_intp ;
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_MEMORY ; 
 int /*<<< orphan*/ * PyArray_GETITEM (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PyObject_Repr (int /*<<< orphan*/ *) ; 
 char* PyString_AsString (int /*<<< orphan*/ *) ; 
 int PyString_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static int
dump_data(char **string, Py_ssize_t *n, Py_ssize_t *max_n, char *data, int nd,
          npy_intp *dimensions, npy_intp *strides, PyArrayObject* self)
{
    PyObject *op = NULL, *sp = NULL;
    char *ostring;
    npy_intp i, N, ret = 0;

#define CHECK_MEMORY do {                           \
        if (extend_str(string, *n, max_n) == NULL) {    \
            ret = -1;                               \
            goto end;                               \
        }                                           \
    } while (0)

    if (nd == 0) {
        if ((op = PyArray_GETITEM(self, data)) == NULL) {
            return -1;
        }
        sp = PyObject_Repr(op);
        if (sp == NULL) {
            ret = -1;
            goto end;
        }
        ostring = PyString_AsString(sp);
        N = PyString_Size(sp)*sizeof(char);
        *n += N;
        CHECK_MEMORY;
        memmove(*string + (*n - N), ostring, N);
    }
    else {
        CHECK_MEMORY;
        (*string)[*n] = '[';
        *n += 1;
        for (i = 0; i < dimensions[0]; i++) {
            if (dump_data(string, n, max_n,
                          data + (*strides)*i,
                          nd - 1, dimensions + 1,
                          strides + 1, self) < 0) {
                return -1;
            }
            CHECK_MEMORY;
            if (i < dimensions[0] - 1) {
                (*string)[*n] = ',';
                (*string)[*n+1] = ' ';
                *n += 2;
            }
        }
        CHECK_MEMORY;
        (*string)[*n] = ']';
        *n += 1;
    }

#undef CHECK_MEMORY

end:
    Py_XDECREF(op);
    Py_XDECREF(sp);
    return ret;
}