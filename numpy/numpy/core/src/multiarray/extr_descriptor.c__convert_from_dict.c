#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_1__ ;

/* Type definitions */
struct TYPE_42__ {int alignment; long elsize; char flags; struct TYPE_42__* metadata; struct TYPE_42__* fields; struct TYPE_42__* names; } ;
typedef  TYPE_1__ PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 char NPY_ALIGNED_STRUCT ; 
 int NPY_FAIL ; 
 char NPY_FROM_FIELDS ; 
 char NPY_NEEDS_PYAPI ; 
 int NPY_NEXT_ALIGNED_OFFSET (int,int) ; 
 int /*<<< orphan*/  NPY_VOID ; 
 int PyArray_DescrAlignConverter (TYPE_1__*,TYPE_1__**) ; 
 int PyArray_DescrConverter (TYPE_1__*,TYPE_1__**) ; 
 TYPE_1__* PyArray_DescrNewFromType (int /*<<< orphan*/ ) ; 
 int PyArray_MAX (int,int) ; 
 long PyArray_PyIntAsInt (TYPE_1__*) ; 
 scalar_t__ PyBaseString_Check (TYPE_1__*) ; 
 scalar_t__ PyDataType_REFCHK (TYPE_1__*) ; 
 int /*<<< orphan*/ * PyDict_GetItem (TYPE_1__*,TYPE_1__*) ; 
 int PyDict_Merge (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItem (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,long,...) ; 
 scalar_t__ PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 TYPE_1__* PyInt_FromLong (int) ; 
 TYPE_1__* PyMapping_GetItemString (TYPE_1__*,char*) ; 
 TYPE_1__* PyObject_GetItem (TYPE_1__*,TYPE_1__*) ; 
 int PyObject_Length (TYPE_1__*) ; 
 int /*<<< orphan*/  PySequence_Tuple (TYPE_1__*) ; 
 int /*<<< orphan*/  PyTuple_Check (TYPE_1__*) ; 
 TYPE_1__* PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 TYPE_1__* Py_False ; 
 TYPE_1__* Py_None ; 
 int /*<<< orphan*/  Py_SETREF (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* Py_True ; 
 int /*<<< orphan*/  Py_XDECREF (TYPE_1__*) ; 
 TYPE_1__* _use_fields_dict (TYPE_1__*,int) ; 
 scalar_t__ error_converting (int) ; 
 scalar_t__ validate_object_field_overlap (TYPE_1__*) ; 

__attribute__((used)) static PyArray_Descr *
_convert_from_dict(PyObject *obj, int align)
{
    PyArray_Descr *new;
    PyObject *fields = NULL;
    PyObject *names  = NULL;
    PyObject *offsets= NULL;
    PyObject *descrs = NULL;
    PyObject *titles = NULL;
    PyObject *metadata, *tmp;
    int n, i;
    int totalsize, itemsize;
    int maxalign = 0;
    /* Types with fields need the Python C API for field access */
    char dtypeflags = NPY_NEEDS_PYAPI;
    int has_out_of_order_fields = 0;

    fields = PyDict_New();
    if (fields == NULL) {
        return (PyArray_Descr *)PyErr_NoMemory();
    }
    /*
     * Use PyMapping_GetItemString to support dictproxy objects as well.
     */
    names = PyMapping_GetItemString(obj, "names");
    if (names == NULL) {
        Py_DECREF(fields);
        /* XXX should check this is a KeyError */
        PyErr_Clear();
        return _use_fields_dict(obj, align);
    }
    descrs = PyMapping_GetItemString(obj, "formats");
    if (descrs == NULL) {
        Py_DECREF(fields);
        /* XXX should check this is a KeyError */
        PyErr_Clear();
        Py_DECREF(names);
        return _use_fields_dict(obj, align);
    }
    n = PyObject_Length(names);
    offsets = PyMapping_GetItemString(obj, "offsets");
    if (!offsets) {
        PyErr_Clear();
    }
    titles = PyMapping_GetItemString(obj, "titles");
    if (!titles) {
        PyErr_Clear();
    }

    if ((n > PyObject_Length(descrs))
        || (offsets && (n > PyObject_Length(offsets)))
        || (titles && (n > PyObject_Length(titles)))) {
        PyErr_SetString(PyExc_ValueError,
                "'names', 'formats', 'offsets', and 'titles' dict "
                "entries must have the same length");
        goto fail;
    }

    /*
     * If a property 'aligned' is in the dict, it overrides the align flag
     * to be True if it not already true.
     */
    tmp = PyMapping_GetItemString(obj, "aligned");
    if (tmp == NULL) {
        PyErr_Clear();
    } else {
        if (tmp == Py_True) {
            align = 1;
        }
        else if (tmp != Py_False) {
            Py_DECREF(tmp);
            PyErr_SetString(PyExc_ValueError,
                    "NumPy dtype descriptor includes 'aligned' entry, "
                    "but its value is neither True nor False");
            goto fail;
        }
        Py_DECREF(tmp);
    }

    totalsize = 0;
    for (i = 0; i < n; i++) {
        PyObject *tup, *descr, *ind, *title, *name, *off;
        int len, ret, _align = 1;
        PyArray_Descr *newdescr;

        /* Build item to insert (descr, offset, [title])*/
        len = 2;
        title = NULL;
        ind = PyInt_FromLong(i);
        if (titles) {
            title=PyObject_GetItem(titles, ind);
            if (title && title != Py_None) {
                len = 3;
            }
            else {
                Py_XDECREF(title);
            }
            PyErr_Clear();
        }
        tup = PyTuple_New(len);
        descr = PyObject_GetItem(descrs, ind);
        if (!descr) {
            Py_DECREF(tup);
            Py_DECREF(ind);
            goto fail;
        }
        if (align) {
            ret = PyArray_DescrAlignConverter(descr, &newdescr);
        }
        else {
            ret = PyArray_DescrConverter(descr, &newdescr);
        }
        Py_DECREF(descr);
        if (ret == NPY_FAIL) {
            Py_DECREF(tup);
            Py_DECREF(ind);
            goto fail;
        }
        PyTuple_SET_ITEM(tup, 0, (PyObject *)newdescr);
        if (align) {
            _align = newdescr->alignment;
            maxalign = PyArray_MAX(maxalign,_align);
        }
        if (offsets) {
            long offset;
            off = PyObject_GetItem(offsets, ind);
            if (!off) {
                Py_DECREF(tup);
                Py_DECREF(ind);
                goto fail;
            }
            offset = PyArray_PyIntAsInt(off);
            if (error_converting(offset)) {
                Py_DECREF(off);
                Py_DECREF(tup);
                Py_DECREF(ind);
                goto fail;
            }
            Py_DECREF(off);
            if (offset < 0) {
                PyErr_Format(PyExc_ValueError, "offset %ld cannot be negative",
                             offset);
                Py_DECREF(tup);
                Py_DECREF(ind);
                goto fail;
            }

            PyTuple_SET_ITEM(tup, 1, PyInt_FromLong(offset));
            /* Flag whether the fields are specified out of order */
            if (offset < totalsize) {
                has_out_of_order_fields = 1;
            }
            /* If align=True, enforce field alignment */
            if (align && offset % newdescr->alignment != 0) {
                PyErr_Format(PyExc_ValueError,
                        "offset %ld for NumPy dtype with fields is "
                        "not divisible by the field alignment %d "
                        "with align=True",
                        offset, newdescr->alignment);
                ret = NPY_FAIL;
            }
            else if (offset + newdescr->elsize > totalsize) {
                totalsize = offset + newdescr->elsize;
            }
        }
        else {
            if (align && _align > 1) {
                totalsize = NPY_NEXT_ALIGNED_OFFSET(totalsize, _align);
            }
            PyTuple_SET_ITEM(tup, 1, PyInt_FromLong(totalsize));
            totalsize += newdescr->elsize;
        }
        if (ret == NPY_FAIL) {
            Py_DECREF(ind);
            Py_DECREF(tup);
            goto fail;
        }
        if (len == 3) {
            PyTuple_SET_ITEM(tup, 2, title);
        }
        name = PyObject_GetItem(names, ind);
        Py_DECREF(ind);
        if (!name) {
            Py_DECREF(tup);
            goto fail;
        }
        if (!PyBaseString_Check(name)) {
            PyErr_SetString(PyExc_ValueError,
                    "field names must be strings");
            Py_DECREF(tup);
            goto fail;
        }

        /* Insert into dictionary */
        if (PyDict_GetItem(fields, name) != NULL) {
            PyErr_SetString(PyExc_ValueError,
                    "name already used as a name or title");
            Py_DECREF(tup);
            goto fail;
        }
        PyDict_SetItem(fields, name, tup);
        Py_DECREF(name);
        if (len == 3) {
            if (PyBaseString_Check(title)) {
                if (PyDict_GetItem(fields, title) != NULL) {
                    PyErr_SetString(PyExc_ValueError,
                            "title already used as a name or title.");
                    Py_DECREF(tup);
                    goto fail;
                }
                PyDict_SetItem(fields, title, tup);
            }
        }
        Py_DECREF(tup);
        if (ret == NPY_FAIL) {
            goto fail;
        }
        dtypeflags |= (newdescr->flags & NPY_FROM_FIELDS);
    }

    new = PyArray_DescrNewFromType(NPY_VOID);
    if (new == NULL) {
        goto fail;
    }
    if (maxalign > 1) {
        totalsize = NPY_NEXT_ALIGNED_OFFSET(totalsize, maxalign);
    }
    if (align) {
        new->alignment = maxalign;
    }
    new->elsize = totalsize;
    if (!PyTuple_Check(names)) {
        Py_SETREF(names, PySequence_Tuple(names));
        if (names == NULL) {
            Py_DECREF(new);
            goto fail;
        }
    }
    new->names = names;
    new->fields = fields;
    new->flags = dtypeflags;
    /* new takes responsibility for DECREFing names, fields */
    names = NULL;
    fields = NULL;

    /*
     * If the fields weren't in order, and there was an OBJECT type,
     * need to verify that no OBJECT types overlap with something else.
     */
    if (has_out_of_order_fields && PyDataType_REFCHK(new)) {
        if (validate_object_field_overlap(new) < 0) {
            Py_DECREF(new);
            goto fail;
        }
    }

    /* Structured arrays get a sticky aligned bit */
    if (align) {
        new->flags |= NPY_ALIGNED_STRUCT;
    }

    /* Override the itemsize if provided */
    tmp = PyMapping_GetItemString(obj, "itemsize");
    if (tmp == NULL) {
        PyErr_Clear();
    } else {
        itemsize = (int)PyArray_PyIntAsInt(tmp);
        Py_DECREF(tmp);
        if (error_converting(itemsize)) {
            Py_DECREF(new);
            goto fail;
        }
        /* Make sure the itemsize isn't made too small */
        if (itemsize < new->elsize) {
            PyErr_Format(PyExc_ValueError,
                    "NumPy dtype descriptor requires %d bytes, "
                    "cannot override to smaller itemsize of %d",
                    new->elsize, itemsize);
            Py_DECREF(new);
            goto fail;
        }
        /* If align is set, make sure the alignment divides into the size */
        if (align && itemsize % new->alignment != 0) {
            PyErr_Format(PyExc_ValueError,
                    "NumPy dtype descriptor requires alignment of %d bytes, "
                    "which is not divisible into the specified itemsize %d",
                    new->alignment, itemsize);
            Py_DECREF(new);
            goto fail;
        }
        /* Set the itemsize */
        new->elsize = itemsize;
    }

    /* Add the metadata if provided */
    metadata = PyMapping_GetItemString(obj, "metadata");

    if (metadata == NULL) {
        PyErr_Clear();
    }
    else if (new->metadata == NULL) {
        new->metadata = metadata;
    }
    else {
        int ret = PyDict_Merge(new->metadata, metadata, 0);
        Py_DECREF(metadata);
        if (ret < 0) {
            Py_DECREF(new);
            goto fail;
        }
    }

    Py_XDECREF(fields);
    Py_XDECREF(names);
    Py_XDECREF(descrs);
    Py_XDECREF(offsets);
    Py_XDECREF(titles);
    return new;

 fail:
    Py_XDECREF(fields);
    Py_XDECREF(names);
    Py_XDECREF(descrs);
    Py_XDECREF(offsets);
    Py_XDECREF(titles);
    return NULL;
}