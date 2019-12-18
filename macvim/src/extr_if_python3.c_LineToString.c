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
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_ERROR_HANDLER ; 
 scalar_t__ ENC_OPT ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/ * PyUnicode_Decode (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ alloc (unsigned int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  vim_free (char*) ; 

__attribute__((used)) static PyObject *
LineToString(const char *str)
{
    PyObject *result;
    Py_ssize_t len = strlen(str);
    char *tmp,*p;

    tmp = (char *)alloc((unsigned)(len+1));
    p = tmp;
    if (p == NULL)
    {
	PyErr_NoMemory();
	return NULL;
    }

    while (*str)
    {
	if (*str == '\n')
	    *p = '\0';
	else
	    *p = *str;

	++p;
	++str;
    }
    *p = '\0';

    result = PyUnicode_Decode(tmp, len, (char *)ENC_OPT, CODEC_ERROR_HANDLER);

    vim_free(tmp);
    return result;
}