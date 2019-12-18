#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* doc; int rank; int /*<<< orphan*/ * data; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  TYPE_2__ FortranDataDef ;

/* Variables and functions */
 TYPE_1__* PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyMem_Free (char*) ; 
 scalar_t__ PyMem_Malloc (int) ; 
 int PyOS_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyString_FromStringAndSize (char*,int) ; 
 int /*<<< orphan*/ * PyUnicode_FromStringAndSize (char*,int) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int format_def (char*,int,TYPE_2__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 

__attribute__((used)) static PyObject *
fortran_doc(FortranDataDef def)
{
    char *buf, *p;
    PyObject *s = NULL;
    Py_ssize_t n, origsize, size = 100;

    if (def.doc != NULL) {
        size += strlen(def.doc);
    }
    origsize = size;
    buf = p = (char *)PyMem_Malloc(size);
    if (buf == NULL) {
        return PyErr_NoMemory();
    }

    if (def.rank == -1) {
        if (def.doc) {
            n = strlen(def.doc);
            if (n > size) {
                goto fail;
            }
            memcpy(p, def.doc, n);
            p += n;
            size -= n;
        }
        else {
            n = PyOS_snprintf(p, size, "%s - no docs available", def.name);
            if (n < 0 || n >= size) {
                goto fail;
            }
            p += n;
            size -= n;
        }
    }
    else {
        PyArray_Descr *d = PyArray_DescrFromType(def.type);
        n = PyOS_snprintf(p, size, "'%c'-", d->type);
        Py_DECREF(d);
        if (n < 0 || n >= size) {
            goto fail;
        }
        p += n;
        size -= n;

        if (def.data == NULL) {
            n = format_def(p, size, def) == -1;
            if (n < 0) {
                goto fail;
            }
            p += n;
            size -= n;
        }
        else if (def.rank > 0) {
            n = format_def(p, size, def);
            if (n < 0) {
                goto fail;
            }
            p += n;
            size -= n;
        }
        else {
            n = strlen("scalar");
            if (size < n) {
                goto fail;
            }
            memcpy(p, "scalar", n);
            p += n;
            size -= n;
        }
    }
    if (size <= 1) {
        goto fail;
    }
    *p++ = '\n';
    size--;

    /* p now points one beyond the last character of the string in buf */
#if PY_VERSION_HEX >= 0x03000000
    s = PyUnicode_FromStringAndSize(buf, p - buf);
#else
    s = PyString_FromStringAndSize(buf, p - buf);
#endif

    PyMem_Free(buf);
    return s;

 fail:
    fprintf(stderr, "fortranobject.c: fortran_doc: len(p)=%zd>%zd=size:"
                    " too long docstring required, increase size\n",
            p - buf, origsize);
    PyMem_Free(buf);
    return NULL;
}