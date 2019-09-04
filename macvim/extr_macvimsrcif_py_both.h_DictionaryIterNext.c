#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ht_array; scalar_t__ ht_used; TYPE_3__* hi; scalar_t__ todo; TYPE_1__* ht; } ;
typedef  TYPE_2__ dictiterinfo_T ;
struct TYPE_7__ {scalar_t__ hi_key; } ;
struct TYPE_5__ {scalar_t__ ht_array; scalar_t__ ht_used; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ HASHITEM_EMPTY (TYPE_3__*) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/ * PyBytes_FromString (char*) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 

__attribute__((used)) static PyObject *
DictionaryIterNext(dictiterinfo_T **dii)
{
    PyObject	*ret;

    if (!(*dii)->todo)
	return NULL;

    if ((*dii)->ht->ht_array != (*dii)->ht_array ||
	    (*dii)->ht->ht_used != (*dii)->ht_used)
    {
	PyErr_SET_STRING(PyExc_RuntimeError,
		N_("hashtab changed during iteration"));
	return NULL;
    }

    while (((*dii)->todo) && HASHITEM_EMPTY((*dii)->hi))
	++((*dii)->hi);

    --((*dii)->todo);

    if (!(ret = PyBytes_FromString((char *)(*dii)->hi->hi_key)))
	return NULL;

    return ret;
}