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
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int NPY_BYTE ; 
 int /*<<< orphan*/ * PyArray_DescrFromType (int) ; 
 scalar_t__ PyArray_DescrNewByteorder (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int _pep3118_letter_to_type (char,int,int) ; 

__attribute__((used)) static int
_descriptor_from_pep3118_format_fast(char *s, PyObject **result)
{
    PyArray_Descr *descr;

    int is_standard_size = 0;
    char byte_order = '=';
    int is_complex = 0;

    int type_num = NPY_BYTE;
    int item_seen = 0;

    for (; *s != '\0'; ++s) {
        is_complex = 0;
        switch (*s) {
        case '@':
        case '^':
            /* ^ means no alignment; doesn't matter for a single element */
            byte_order = '=';
            is_standard_size = 0;
            break;
        case '<':
            byte_order = '<';
            is_standard_size = 1;
            break;
        case '>':
        case '!':
            byte_order = '>';
            is_standard_size = 1;
            break;
        case '=':
            byte_order = '=';
            is_standard_size = 1;
            break;
        case 'Z':
            is_complex = 1;
            ++s;
        default:
            if (item_seen) {
                /* Not a single-element data type */
                return 0;
            }
            type_num = _pep3118_letter_to_type(*s, !is_standard_size,
                                               is_complex);
            if (type_num < 0) {
                /* Something unknown */
                return 0;
            }
            item_seen = 1;
            break;
        }
    }

    if (!item_seen) {
        return 0;
    }

    descr = PyArray_DescrFromType(type_num);
    if (byte_order == '=') {
        *result = (PyObject*)descr;
    }
    else {
        *result = (PyObject*)PyArray_DescrNewByteorder(descr, byte_order);
        Py_DECREF(descr);
    }

    return 1;
}