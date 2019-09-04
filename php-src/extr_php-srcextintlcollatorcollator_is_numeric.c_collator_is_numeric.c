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
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  int int32_t ;
typedef  char UChar ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  E_NOTICE ; 
 int /*<<< orphan*/  IS_DOUBLE ; 
 int /*<<< orphan*/  IS_LONG ; 
 double collator_u_strtod (char*,char**) ; 
 int /*<<< orphan*/  collator_u_strtol (char*,char**,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_finite (double) ; 

zend_uchar collator_is_numeric( UChar *str, int32_t length, zend_long *lval, double *dval, int allow_errors )
{
	zend_long local_lval;
	double local_dval;
	UChar *end_ptr_long, *end_ptr_double;
	int conv_base=10;

	if (!length) {
		return 0;
	}

	/* handle hex numbers */
	if (length>=2 && str[0]=='0' && (str[1]=='x' || str[1]=='X')) {
		conv_base=16;
	}

	errno=0;
	local_lval = collator_u_strtol(str, &end_ptr_long, conv_base);
	if (errno != ERANGE) {
		if (end_ptr_long == str+length) { /* integer string */
			if (lval) {
				*lval = local_lval;
			}
			return IS_LONG;
		} else if (end_ptr_long == str && *end_ptr_long != '\0' && *str != '.' && *str != '-') { /* ignore partial string matches */
			return 0;
		}
	} else {
		end_ptr_long = NULL;
	}

	if (conv_base == 16) { /* hex string, under UNIX strtod() messes it up */
		/* UTODO: keep compatibility with is_numeric_string() here? */
		return 0;
	}

	local_dval = collator_u_strtod(str, &end_ptr_double);
	if (local_dval == 0 && end_ptr_double == str) {
		end_ptr_double = NULL;
	} else {
		if (end_ptr_double == str+length) { /* floating point string */
			if (!zend_finite(local_dval)) {
				/* "inf","nan" and maybe other weird ones */
				return 0;
			}

			if (dval) {
				*dval = local_dval;
			}
			return IS_DOUBLE;
		}
	}

	if (!allow_errors) {
		return 0;
	}
	if (allow_errors == -1) {
		zend_error(E_NOTICE, "A non well formed numeric value encountered");
	}

	if (allow_errors) {
		if (end_ptr_double > end_ptr_long && dval) {
			*dval = local_dval;
			return IS_DOUBLE;
		} else if (end_ptr_long && lval) {
			*lval = local_lval;
			return IS_LONG;
		}
	}
	return 0;
}