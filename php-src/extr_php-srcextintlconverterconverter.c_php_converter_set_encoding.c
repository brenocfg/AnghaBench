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
typedef  int zend_bool ;
typedef  int /*<<< orphan*/  php_converter_object ;
typedef  scalar_t__ UErrorCode ;
typedef  int /*<<< orphan*/  UConverter ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  THROW_UFAILURE (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ U_AMBIGUOUS_ALIAS_WARNING ; 
 scalar_t__ U_FAILURE (scalar_t__) ; 
 scalar_t__ U_ZERO_ERROR ; 
 int /*<<< orphan*/  php_converter_set_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  u_errorName (scalar_t__) ; 
 int /*<<< orphan*/  ucnv_close (int /*<<< orphan*/ *) ; 
 char* ucnv_getName (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * ucnv_open (char const*,scalar_t__*) ; 

__attribute__((used)) static zend_bool php_converter_set_encoding(php_converter_object *objval,
                                            UConverter **pcnv,
                                            const char *enc, size_t enc_len
                                           ) {
	UErrorCode error = U_ZERO_ERROR;
	UConverter *cnv = ucnv_open(enc, &error);

	if (error == U_AMBIGUOUS_ALIAS_WARNING) {
		UErrorCode getname_error = U_ZERO_ERROR;
		const char *actual_encoding = ucnv_getName(cnv, &getname_error);
		if (U_FAILURE(getname_error)) {
			/* Should never happen */
			actual_encoding = "(unknown)";
		}
		php_error_docref(NULL, E_WARNING, "Ambiguous encoding specified, using %s", actual_encoding);
	} else if (U_FAILURE(error)) {
		if (objval) {
			THROW_UFAILURE(objval, "ucnv_open", error);
		} else {
			php_error_docref(NULL, E_WARNING, "Error setting encoding: %d - %s", (int)error, u_errorName(error));
		}
		return 0;
	}

	if (objval && !php_converter_set_callbacks(objval, cnv)) {
		return 0;
	}

	if (*pcnv) {
		ucnv_close(*pcnv);
	}
	*pcnv = cnv;
	return 1;
}