#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_63__   TYPE_57__ ;
typedef  struct TYPE_62__   TYPE_3__ ;
typedef  struct TYPE_61__   TYPE_1__ ;

/* Type definitions */
struct TYPE_63__ {TYPE_1__* shape; TYPE_1__* base; } ;
struct TYPE_62__ {int /*<<< orphan*/  meta; } ;
struct TYPE_61__ {int hash; char byteorder; int elsize; int alignment; char flags; struct TYPE_61__* metadata; scalar_t__ c_metadata; int /*<<< orphan*/  type_num; struct TYPE_61__* fields; struct TYPE_61__* names; TYPE_57__* subarray; } ;
typedef  int Py_ssize_t ;
typedef  TYPE_1__ PyObject ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArray_DatetimeMetaData ;
typedef  TYPE_3__ PyArray_DatetimeDTypeMetaData ;
typedef  int /*<<< orphan*/  PyArray_ArrayDescr ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_TRUE ; 
 int /*<<< orphan*/  PyArg_ParseTuple (TYPE_1__*,char*,...) ; 
 scalar_t__ PyArray_DescrCheck (TYPE_1__*) ; 
 scalar_t__ PyArray_IsNativeByteOrder (char) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_57__*) ; 
 TYPE_57__* PyArray_malloc (int) ; 
 scalar_t__ PyBytes_AsStringAndSize (TYPE_1__*,char**,int*) ; 
 scalar_t__ PyBytes_Check (TYPE_1__*) ; 
 int /*<<< orphan*/  PyDataType_HASSUBARRAY (TYPE_1__*) ; 
 scalar_t__ PyDataType_ISDATETIME (TYPE_1__*) ; 
 int /*<<< orphan*/  PyDict_Check (TYPE_1__*) ; 
 int /*<<< orphan*/  PyDict_DelItem (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* PyDict_GetItem (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* PyDict_New () ; 
 scalar_t__ PyDict_SetItem (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PyErr_BadInternalCall () ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int PyInt_AsLong (TYPE_1__*) ; 
 TYPE_1__* PyInt_FromLong (int) ; 
 scalar_t__ PyNumber_Check (TYPE_1__*) ; 
 TYPE_1__* PyNumber_Int (TYPE_1__*) ; 
 TYPE_1__* PyNumber_Long (TYPE_1__*) ; 
 int /*<<< orphan*/  PyObject_Repr (TYPE_1__*) ; 
 scalar_t__ PyTuple_Check (TYPE_1__*) ; 
 TYPE_1__* PyTuple_GET_ITEM (TYPE_1__*,int) ; 
 int PyTuple_GET_SIZE (TYPE_1__*) ; 
 TYPE_1__* PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (TYPE_1__*,int,TYPE_1__*) ; 
 int PyTuple_Size (TYPE_1__*) ; 
 scalar_t__ PyTypeNum_ISEXTENDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyUString_Check (TYPE_1__*) ; 
 int /*<<< orphan*/  PyUString_ConcatAndDel (TYPE_1__**,int /*<<< orphan*/ ) ; 
 TYPE_1__* PyUString_FromString (char*) ; 
 TYPE_1__* PyUnicode_AsASCIIString (TYPE_1__*) ; 
 scalar_t__ PyUnicode_Check (TYPE_1__*) ; 
 TYPE_1__* PyUnicode_FromEncodedObject (TYPE_1__*,char*,char*) ; 
 TYPE_1__* Py_BuildValue (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_1__*) ; 
 TYPE_1__* Py_None ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  Py_XDECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XINCREF (TYPE_1__*) ; 
 char _descr_find_object (TYPE_1__*) ; 
 scalar_t__ _is_tuple_of_integers (TYPE_1__*) ; 
 scalar_t__ convert_datetime_metadata_tuple_to_datetime_metadata (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static PyObject *
arraydescr_setstate(PyArray_Descr *self, PyObject *args)
{
    int elsize = -1, alignment = -1;
    int version = 4;
    char endian;
    PyObject *endian_obj;
    PyObject *subarray, *fields, *names = NULL, *metadata=NULL;
    int incref_names = 1;
    int int_dtypeflags = 0;
    char dtypeflags;

    if (self->fields == Py_None) {
        Py_RETURN_NONE;
    }
    if (PyTuple_GET_SIZE(args) != 1
            || !(PyTuple_Check(PyTuple_GET_ITEM(args, 0)))) {
        PyErr_BadInternalCall();
        return NULL;
    }
    switch (PyTuple_GET_SIZE(PyTuple_GET_ITEM(args,0))) {
    case 9:
        if (!PyArg_ParseTuple(args, "(iOOOOiiiO):__setstate__",
                    &version, &endian_obj,
                    &subarray, &names, &fields, &elsize,
                    &alignment, &int_dtypeflags, &metadata)) {
            PyErr_Clear();
            return NULL;
        }
        break;
    case 8:
        if (!PyArg_ParseTuple(args, "(iOOOOiii):__setstate__",
                    &version, &endian_obj,
                    &subarray, &names, &fields, &elsize,
                    &alignment, &int_dtypeflags)) {
            return NULL;
        }
        break;
    case 7:
        if (!PyArg_ParseTuple(args, "(iOOOOii):__setstate__",
                    &version, &endian_obj,
                    &subarray, &names, &fields, &elsize,
                    &alignment)) {
            return NULL;
        }
        break;
    case 6:
        if (!PyArg_ParseTuple(args, "(iOOOii):__setstate__",
                    &version,
                    &endian_obj, &subarray, &fields,
                    &elsize, &alignment)) {
            return NULL;
        }
        break;
    case 5:
        version = 0;
        if (!PyArg_ParseTuple(args, "(OOOii):__setstate__",
                    &endian_obj, &subarray, &fields, &elsize,
                    &alignment)) {
            return NULL;
        }
        break;
    default:
        /* raise an error */
        if (PyTuple_GET_SIZE(PyTuple_GET_ITEM(args,0)) > 5) {
            version = PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
        }
        else {
            version = -1;
        }
    }

    /*
     * If we ever need another pickle format, increment the version
     * number. But we should still be able to handle the old versions.
     */
    if (version < 0 || version > 4) {
        PyErr_Format(PyExc_ValueError,
                     "can't handle version %d of numpy.dtype pickle",
                     version);
        return NULL;
    }
    /* Invalidate cached hash value */
    self->hash = -1;

    if (version == 1 || version == 0) {
        if (fields != Py_None) {
            PyObject *key, *list;
            key = PyInt_FromLong(-1);
            list = PyDict_GetItem(fields, key);
            if (!list) {
                return NULL;
            }
            Py_INCREF(list);
            names = list;
            PyDict_DelItem(fields, key);
            incref_names = 0;
        }
        else {
            names = Py_None;
        }
    }

    /* Parse endian */
    if (PyUnicode_Check(endian_obj) || PyBytes_Check(endian_obj)) {
        PyObject *tmp = NULL;
        char *str;
        Py_ssize_t len;

        if (PyUnicode_Check(endian_obj)) {
            tmp = PyUnicode_AsASCIIString(endian_obj);
            if (tmp == NULL) {
                return NULL;
            }
            endian_obj = tmp;
        }

        if (PyBytes_AsStringAndSize(endian_obj, &str, &len) < 0) {
            Py_XDECREF(tmp);
            return NULL;
        }
        if (len != 1) {
            PyErr_SetString(PyExc_ValueError,
                            "endian is not 1-char string in Numpy dtype unpickling");
            Py_XDECREF(tmp);
            return NULL;
        }
        endian = str[0];
        Py_XDECREF(tmp);
    }
    else {
        PyErr_SetString(PyExc_ValueError,
                        "endian is not a string in Numpy dtype unpickling");
        return NULL;
    }

    if ((fields == Py_None && names != Py_None) ||
        (names == Py_None && fields != Py_None)) {
        PyErr_Format(PyExc_ValueError,
                "inconsistent fields and names in Numpy dtype unpickling");
        return NULL;
    }

    if (names != Py_None && !PyTuple_Check(names)) {
        PyErr_Format(PyExc_ValueError,
                "non-tuple names in Numpy dtype unpickling");
        return NULL;
    }

    if (fields != Py_None && !PyDict_Check(fields)) {
        PyErr_Format(PyExc_ValueError,
                "non-dict fields in Numpy dtype unpickling");
        return NULL;
    }

    if (endian != '|' && PyArray_IsNativeByteOrder(endian)) {
        endian = '=';
    }
    self->byteorder = endian;
    if (self->subarray) {
        Py_XDECREF(self->subarray->base);
        Py_XDECREF(self->subarray->shape);
        PyArray_free(self->subarray);
    }
    self->subarray = NULL;

    if (subarray != Py_None) {
        PyObject *subarray_shape;

        /*
         * Ensure that subarray[0] is an ArrayDescr and
         * that subarray_shape obtained from subarray[1] is a tuple of integers.
         */
        if (!(PyTuple_Check(subarray) &&
              PyTuple_Size(subarray) == 2 &&
              PyArray_DescrCheck(PyTuple_GET_ITEM(subarray, 0)))) {
            PyErr_Format(PyExc_ValueError,
                         "incorrect subarray in __setstate__");
            return NULL;
        }
        subarray_shape = PyTuple_GET_ITEM(subarray, 1);
        if (PyNumber_Check(subarray_shape)) {
            PyObject *tmp;
#if defined(NPY_PY3K)
            tmp = PyNumber_Long(subarray_shape);
#else
            tmp = PyNumber_Int(subarray_shape);
#endif
            if (tmp == NULL) {
                return NULL;
            }
            subarray_shape = Py_BuildValue("(O)", tmp);
            Py_DECREF(tmp);
            if (subarray_shape == NULL) {
                return NULL;
            }
        }
        else if (_is_tuple_of_integers(subarray_shape)) {
            Py_INCREF(subarray_shape);
        }
        else {
            PyErr_Format(PyExc_ValueError,
                         "incorrect subarray shape in __setstate__");
            return NULL;
        }

        self->subarray = PyArray_malloc(sizeof(PyArray_ArrayDescr));
        if (!PyDataType_HASSUBARRAY(self)) {
            return PyErr_NoMemory();
        }
        self->subarray->base = (PyArray_Descr *)PyTuple_GET_ITEM(subarray, 0);
        Py_INCREF(self->subarray->base);
        self->subarray->shape = subarray_shape;
    }

    if (fields != Py_None) {
        /*
         * Ensure names are of appropriate string type
         */
        Py_ssize_t i;
        int names_ok = 1;
        PyObject *name;

        for (i = 0; i < PyTuple_GET_SIZE(names); ++i) {
            name = PyTuple_GET_ITEM(names, i);
            if (!PyUString_Check(name)) {
                names_ok = 0;
                break;
            }
        }

        if (names_ok) {
            Py_XDECREF(self->fields);
            self->fields = fields;
            Py_INCREF(fields);
            Py_XDECREF(self->names);
            self->names = names;
            if (incref_names) {
                Py_INCREF(names);
            }
        }
        else {
#if defined(NPY_PY3K)
            /*
             * To support pickle.load(f, encoding='bytes') for loading Py2
             * generated pickles on Py3, we need to be more lenient and convert
             * field names from byte strings to unicode.
             */
            PyObject *tmp, *new_name, *field;

            tmp = PyDict_New();
            if (tmp == NULL) {
                return NULL;
            }
            Py_XDECREF(self->fields);
            self->fields = tmp;

            tmp = PyTuple_New(PyTuple_GET_SIZE(names));
            if (tmp == NULL) {
                return NULL;
            }
            Py_XDECREF(self->names);
            self->names = tmp;

            for (i = 0; i < PyTuple_GET_SIZE(names); ++i) {
                name = PyTuple_GET_ITEM(names, i);
                field = PyDict_GetItem(fields, name);
                if (!field) {
                    return NULL;
                }

                if (PyUnicode_Check(name)) {
                    new_name = name;
                    Py_INCREF(new_name);
                }
                else {
                    new_name = PyUnicode_FromEncodedObject(name, "ASCII", "strict");
                    if (new_name == NULL) {
                        return NULL;
                    }
                }

                PyTuple_SET_ITEM(self->names, i, new_name);
                if (PyDict_SetItem(self->fields, new_name, field) != 0) {
                    return NULL;
                }
            }
#else
            PyErr_Format(PyExc_ValueError,
                "non-string names in Numpy dtype unpickling");
            return NULL;
#endif
        }
    }

    if (PyTypeNum_ISEXTENDED(self->type_num)) {
        self->elsize = elsize;
        self->alignment = alignment;
    }

    /*
     * We use an integer converted to char for backward compatibility with
     * pickled arrays. Pickled arrays created with previous versions encoded
     * flags as an int even though it actually was a char in the PyArray_Descr
     * structure
     */
    dtypeflags = int_dtypeflags;
    if (dtypeflags != int_dtypeflags) {
        PyErr_Format(PyExc_ValueError,
                     "incorrect value for flags variable (overflow)");
        return NULL;
    }
    else {
        self->flags = dtypeflags;
    }

    if (version < 3) {
        self->flags = _descr_find_object(self);
    }

    /*
     * We have a borrowed reference to metadata so no need
     * to alter reference count when throwing away Py_None.
     */
    if (metadata == Py_None) {
        metadata = NULL;
    }

    if (PyDataType_ISDATETIME(self) && (metadata != NULL)) {
        PyObject *old_metadata, *errmsg;
        PyArray_DatetimeMetaData temp_dt_data;

        if ((! PyTuple_Check(metadata)) || (PyTuple_Size(metadata) != 2)) {
            errmsg = PyUString_FromString("Invalid datetime dtype (metadata, c_metadata): ");
            PyUString_ConcatAndDel(&errmsg, PyObject_Repr(metadata));
            PyErr_SetObject(PyExc_ValueError, errmsg);
            Py_DECREF(errmsg);
            return NULL;
        }

        if (convert_datetime_metadata_tuple_to_datetime_metadata(
                                    PyTuple_GET_ITEM(metadata, 1),
                                    &temp_dt_data,
                                    NPY_TRUE) < 0) {
            return NULL;
        }

        old_metadata = self->metadata;
        self->metadata = PyTuple_GET_ITEM(metadata, 0);
        memcpy((char *) &((PyArray_DatetimeDTypeMetaData *)self->c_metadata)->meta,
               (char *) &temp_dt_data,
               sizeof(PyArray_DatetimeMetaData));
        Py_XINCREF(self->metadata);
        Py_XDECREF(old_metadata);
    }
    else {
        PyObject *old_metadata = self->metadata;
        self->metadata = metadata;
        Py_XINCREF(self->metadata);
        Py_XDECREF(old_metadata);
    }

    Py_RETURN_NONE;
}