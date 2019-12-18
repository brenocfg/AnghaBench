#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;

/* Type definitions */
typedef  void* varnumber_T ;
struct TYPE_40__ {void* v_number; scalar_t__ v_float; int /*<<< orphan*/  v_string; TYPE_2__* v_list; TYPE_1__* v_dict; } ;
struct TYPE_41__ {TYPE_3__ vval; void* v_type; } ;
typedef  TYPE_4__ typval_T ;
typedef  scalar_t__ float_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_45__ {TYPE_1__* dict; } ;
struct TYPE_44__ {int /*<<< orphan*/ * name; } ;
struct TYPE_43__ {TYPE_2__* list; } ;
struct TYPE_42__ {int /*<<< orphan*/  ob_type; } ;
struct TYPE_39__ {int /*<<< orphan*/  lv_refcount; } ;
struct TYPE_38__ {int /*<<< orphan*/  dv_refcount; } ;
typedef  TYPE_5__ PyObject ;
typedef  TYPE_6__ ListObject ;
typedef  TYPE_7__ FunctionObject ;
typedef  TYPE_8__ DictionaryObject ;

/* Variables and functions */
 int /*<<< orphan*/  DictionaryType ; 
 int /*<<< orphan*/  ENC_OPT ; 
 int /*<<< orphan*/  FunctionType ; 
 int /*<<< orphan*/  ListType ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int PyBytes_AsStringAndSize (TYPE_5__*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ PyBytes_Check (TYPE_5__*) ; 
 scalar_t__ PyDict_Check (TYPE_5__*) ; 
 int /*<<< orphan*/  PyErr_FORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 scalar_t__ PyFloat_AsDouble (TYPE_5__*) ; 
 scalar_t__ PyFloat_Check (TYPE_5__*) ; 
 scalar_t__ PyInt_AsLong (TYPE_5__*) ; 
 scalar_t__ PyInt_Check (TYPE_5__*) ; 
 scalar_t__ PyIter_Check (TYPE_5__*) ; 
 scalar_t__ PyLong_AsLong (TYPE_5__*) ; 
 scalar_t__ PyLong_Check (TYPE_5__*) ; 
 scalar_t__ PyMapping_Check (TYPE_5__*) ; 
 scalar_t__ PyNumber_Check (TYPE_5__*) ; 
 TYPE_5__* PyNumber_Long (TYPE_5__*) ; 
 scalar_t__ PyObject_HasAttrString (TYPE_5__*,char*) ; 
 scalar_t__ PySequence_Check (TYPE_5__*) ; 
 scalar_t__ PyType_IsSubtype (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* PyUnicode_AsEncodedString (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (TYPE_5__*) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_5__*) ; 
 int /*<<< orphan*/  Py_TYPE_NAME (TYPE_5__*) ; 
 int /*<<< orphan*/  Py_XDECREF (TYPE_5__*) ; 
 void* VAR_DICT ; 
 void* VAR_FLOAT ; 
 void* VAR_FUNC ; 
 void* VAR_LIST ; 
 void* VAR_NUMBER ; 
 void* VAR_STRING ; 
 int convert_dl (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  func_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pydict_to_tv ; 
 int /*<<< orphan*/  pymap_to_tv ; 
 int /*<<< orphan*/  pyseq_to_tv ; 
 int set_string_copy (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static int
_ConvertFromPyObject(PyObject *obj, typval_T *tv, PyObject *lookup_dict)
{
    if (PyType_IsSubtype(obj->ob_type, &DictionaryType))
    {
	tv->v_type = VAR_DICT;
	tv->vval.v_dict = (((DictionaryObject *)(obj))->dict);
	++tv->vval.v_dict->dv_refcount;
    }
    else if (PyType_IsSubtype(obj->ob_type, &ListType))
    {
	tv->v_type = VAR_LIST;
	tv->vval.v_list = (((ListObject *)(obj))->list);
	++tv->vval.v_list->lv_refcount;
    }
    else if (PyType_IsSubtype(obj->ob_type, &FunctionType))
    {
	if (set_string_copy(((FunctionObject *) (obj))->name, tv) == -1)
	    return -1;

	tv->v_type = VAR_FUNC;
	func_ref(tv->vval.v_string);
    }
    else if (PyBytes_Check(obj))
    {
	char_u	*str;

	if (PyBytes_AsStringAndSize(obj, (char **) &str, NULL) == -1)
	    return -1;
	if (str == NULL)
	    return -1;

	if (set_string_copy(str, tv) == -1)
	    return -1;

	tv->v_type = VAR_STRING;
    }
    else if (PyUnicode_Check(obj))
    {
	PyObject	*bytes;
	char_u	*str;

	bytes = PyUnicode_AsEncodedString(obj, ENC_OPT, NULL);
	if (bytes == NULL)
	    return -1;

	if(PyBytes_AsStringAndSize(bytes, (char **) &str, NULL) == -1)
	    return -1;
	if (str == NULL)
	    return -1;

	if (set_string_copy(str, tv))
	{
	    Py_XDECREF(bytes);
	    return -1;
	}
	Py_XDECREF(bytes);

	tv->v_type = VAR_STRING;
    }
#if PY_MAJOR_VERSION < 3
    else if (PyInt_Check(obj))
    {
	tv->v_type = VAR_NUMBER;
	tv->vval.v_number = (varnumber_T) PyInt_AsLong(obj);
	if (PyErr_Occurred())
	    return -1;
    }
#endif
    else if (PyLong_Check(obj))
    {
	tv->v_type = VAR_NUMBER;
	tv->vval.v_number = (varnumber_T) PyLong_AsLong(obj);
	if (PyErr_Occurred())
	    return -1;
    }
    else if (PyDict_Check(obj))
	return convert_dl(obj, tv, pydict_to_tv, lookup_dict);
#ifdef FEAT_FLOAT
    else if (PyFloat_Check(obj))
    {
	tv->v_type = VAR_FLOAT;
	tv->vval.v_float = (float_T) PyFloat_AsDouble(obj);
    }
#endif
    else if (PyObject_HasAttrString(obj, "keys"))
	return convert_dl(obj, tv, pymap_to_tv, lookup_dict);
    /* PyObject_GetIter can create built-in iterator for any sequence object */
    else if (PyIter_Check(obj) || PySequence_Check(obj))
	return convert_dl(obj, tv, pyseq_to_tv, lookup_dict);
    else if (PyMapping_Check(obj))
	return convert_dl(obj, tv, pymap_to_tv, lookup_dict);
    else if (PyNumber_Check(obj))
    {
	PyObject	*num;

	if (!(num = PyNumber_Long(obj)))
	    return -1;

	tv->v_type = VAR_NUMBER;
	tv->vval.v_number = (varnumber_T) PyLong_AsLong(num);

	Py_DECREF(num);
    }
    else
    {
	PyErr_FORMAT(PyExc_TypeError,
		N_("unable to convert %s to vim structure"),
		Py_TYPE_NAME(obj));
	return -1;
    }
    return 0;
}