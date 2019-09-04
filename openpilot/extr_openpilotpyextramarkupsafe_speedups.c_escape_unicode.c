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
typedef  int Py_ssize_t ;
typedef  size_t const Py_UNICODE ;
typedef  int /*<<< orphan*/  PyUnicodeObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 size_t const ESCAPED_CHARS_TABLE_SIZE ; 
 size_t const* PyUnicode_AS_UNICODE (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_FromUnicode (int /*<<< orphan*/ *,int) ; 
 int PyUnicode_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_UNICODE_COPY (size_t const*,size_t const*,int) ; 
 int* escaped_chars_delta_len ; 
 size_t const** escaped_chars_repl ; 

__attribute__((used)) static PyObject*
escape_unicode(PyUnicodeObject *in)
{
	PyUnicodeObject *out;
	Py_UNICODE *inp = PyUnicode_AS_UNICODE(in);
	const Py_UNICODE *inp_end = PyUnicode_AS_UNICODE(in) + PyUnicode_GET_SIZE(in);
	Py_UNICODE *next_escp;
	Py_UNICODE *outp;
	Py_ssize_t delta=0, erepl=0, delta_len=0;

	/* First we need to figure out how long the escaped string will be */
	while (*(inp) || inp < inp_end) {
		if (*inp < ESCAPED_CHARS_TABLE_SIZE) {
			delta += escaped_chars_delta_len[*inp];
			erepl += !!escaped_chars_delta_len[*inp];
		}
		++inp;
	}

	/* Do we need to escape anything at all? */
	if (!erepl) {
		Py_INCREF(in);
		return (PyObject*)in;
	}

	out = (PyUnicodeObject*)PyUnicode_FromUnicode(NULL, PyUnicode_GET_SIZE(in) + delta);
	if (!out)
		return NULL;

	outp = PyUnicode_AS_UNICODE(out);
	inp = PyUnicode_AS_UNICODE(in);
	while (erepl-- > 0) {
		/* look for the next substitution */
		next_escp = inp;
		while (next_escp < inp_end) {
			if (*next_escp < ESCAPED_CHARS_TABLE_SIZE &&
			    (delta_len = escaped_chars_delta_len[*next_escp])) {
				++delta_len;
				break;
			}
			++next_escp;
		}

		if (next_escp > inp) {
			/* copy unescaped chars between inp and next_escp */
			Py_UNICODE_COPY(outp, inp, next_escp-inp);
			outp += next_escp - inp;
		}

		/* escape 'next_escp' */
		Py_UNICODE_COPY(outp, escaped_chars_repl[*next_escp], delta_len);
		outp += delta_len;

		inp = next_escp + 1;
	}
	if (inp < inp_end)
		Py_UNICODE_COPY(outp, inp, PyUnicode_GET_SIZE(in) - (inp - PyUnicode_AS_UNICODE(in)));

	return (PyObject*)out;
}