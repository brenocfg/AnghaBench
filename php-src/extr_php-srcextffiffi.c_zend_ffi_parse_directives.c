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
typedef  scalar_t__ zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  zend_ffi_exception_ce ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static char *zend_ffi_parse_directives(const char *filename, char *code_pos, char **scope_name, char **lib, zend_bool preload) /* {{{ */
{
	char *p;

	*scope_name = NULL;
	*lib = NULL;
	while (*code_pos == '#') {
		if (strncmp(code_pos, "#define FFI_SCOPE", sizeof("#define FFI_SCOPE") - 1) == 0
		 && (code_pos[sizeof("#define FFI_SCOPE") - 1] == ' '
		  || code_pos[sizeof("#define FFI_SCOPE") - 1] == '\t')) {
			p = code_pos + sizeof("#define FFI_SCOPE");
			while (*p == ' ' || *p == '\t') {
				p++;
			}
			if (*p != '"') {
				if (preload) {
					zend_error(E_WARNING, "FFI: failed pre-loading '%s', bad FFI_SCOPE define", filename);
				} else {
					zend_throw_error(zend_ffi_exception_ce, "Failed loading '%s', bad FFI_SCOPE define", filename);
				}
				return NULL;
			}
			p++;
			if (*scope_name) {
				if (preload) {
					zend_error(E_WARNING, "FFI: failed pre-loading '%s', FFI_SCOPE defined twice", filename);
				} else {
					zend_throw_error(zend_ffi_exception_ce, "Failed loading '%s', FFI_SCOPE defined twice", filename);
				}
				return NULL;
			}
			*scope_name = p;
			while (1) {
				if (*p == '\"') {
					*p = 0;
					p++;
					break;
				} else if (*p <= ' ') {
					if (preload) {
						zend_error(E_WARNING, "FFI: failed pre-loading '%s', bad FFI_SCOPE define", filename);
					} else {
						zend_throw_error(zend_ffi_exception_ce, "Failed loading '%s', bad FFI_SCOPE define", filename);
					}
					return NULL;
				}
				p++;
			}
			while (*p == ' ' || *p == '\t') {
				p++;
			}
			while (*p == '\r' || *p == '\n') {
				p++;
			}
			code_pos = p;
		} else if (strncmp(code_pos, "#define FFI_LIB", sizeof("#define FFI_LIB") - 1) == 0
		 && (code_pos[sizeof("#define FFI_LIB") - 1] == ' '
		  || code_pos[sizeof("#define FFI_LIB") - 1] == '\t')) {
			p = code_pos + sizeof("#define FFI_LIB");
			while (*p == ' ' || *p == '\t') {
				p++;
			}
			if (*p != '"') {
				if (preload) {
					zend_error(E_WARNING, "FFI: failed pre-loading '%s', bad FFI_LIB define", filename);
				} else {
					zend_throw_error(zend_ffi_exception_ce, "Failed loading '%s', bad FFI_LIB define", filename);
				}
				return NULL;
			}
			p++;
			if (*lib) {
				if (preload) {
					zend_error(E_WARNING, "FFI: failed pre-loading '%s', FFI_LIB defined twice", filename);
				} else {
					zend_throw_error(zend_ffi_exception_ce, "Failed loading '%s', FFI_LIB defined twice", filename);
				}
				return NULL;
			}
			*lib = p;
			while (1) {
				if (*p == '\"') {
					*p = 0;
					p++;
					break;
				} else if (*p <= ' ') {
					if (preload) {
						zend_error(E_WARNING, "FFI: failed pre-loading '%s', bad FFI_LIB define", filename);
					} else {
						zend_throw_error(zend_ffi_exception_ce, "Failed loading '%s', bad FFI_LIB define", filename);
					}
					return NULL;
				}
				p++;
			}
			while (*p == ' ' || *p == '\t') {
				p++;
			}
			while (*p == '\r' || *p == '\n') {
				p++;
			}
			code_pos = p;
		} else {
			break;
		}
	}
	return code_pos;
}