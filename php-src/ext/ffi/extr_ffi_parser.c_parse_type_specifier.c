#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ zend_ffi_dcl ;

/* Variables and functions */
#define  YY_CHAR 145 
#define  YY_COMPLEX 144 
#define  YY_DOUBLE 143 
#define  YY_ENUM 142 
#define  YY_FLOAT 141 
#define  YY_ID 140 
#define  YY_INT 139 
#define  YY_LONG 138 
#define  YY_SHORT 137 
#define  YY_SIGNED 136 
#define  YY_STRUCT 135 
#define  YY_UNION 134 
#define  YY_UNSIGNED 133 
#define  YY_VOID 132 
#define  YY__BOOL 131 
#define  YY__COMPLEX 130 
#define  YY___COMPLEX 129 
#define  YY___COMPLEX__ 128 
 int ZEND_FFI_DCL_BOOL ; 
 int ZEND_FFI_DCL_CHAR ; 
 int ZEND_FFI_DCL_COMPLEX ; 
 int ZEND_FFI_DCL_DOUBLE ; 
 int ZEND_FFI_DCL_FLOAT ; 
 int ZEND_FFI_DCL_INT ; 
 int ZEND_FFI_DCL_LONG ; 
 int ZEND_FFI_DCL_LONG_LONG ; 
 int ZEND_FFI_DCL_SHORT ; 
 int ZEND_FFI_DCL_SIGNED ; 
 int ZEND_FFI_DCL_TYPEDEF_NAME ; 
 int ZEND_FFI_DCL_TYPE_SPECIFIERS ; 
 int ZEND_FFI_DCL_UNSIGNED ; 
 int ZEND_FFI_DCL_VOID ; 
 int get_sym () ; 
 int parse_ID (int,char const**,size_t*) ; 
 int parse_enum_specifier (int,TYPE_1__*) ; 
 int parse_struct_or_union_specifier (int,TYPE_1__*) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_resolve_typedef (char const*,size_t,TYPE_1__*) ; 

__attribute__((used)) static int parse_type_specifier(int sym, zend_ffi_dcl *dcl) {
	const char *name;
	size_t name_len;
	switch (sym) {
		case YY_VOID:
			if (dcl->flags & ZEND_FFI_DCL_TYPE_SPECIFIERS) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_VOID;
			break;
		case YY_CHAR:
			if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_SIGNED|ZEND_FFI_DCL_UNSIGNED))) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_CHAR;
			break;
		case YY_SHORT:
			if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_SIGNED|ZEND_FFI_DCL_UNSIGNED|ZEND_FFI_DCL_INT))) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_SHORT;
			break;
		case YY_INT:
			if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_SIGNED|ZEND_FFI_DCL_UNSIGNED|ZEND_FFI_DCL_SHORT|ZEND_FFI_DCL_LONG|ZEND_FFI_DCL_LONG_LONG))) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_INT;
			break;
		case YY_LONG:
			if (dcl->flags & ZEND_FFI_DCL_LONG) {
				if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_LONG|ZEND_FFI_DCL_SIGNED|ZEND_FFI_DCL_UNSIGNED|ZEND_FFI_DCL_INT))) yy_error_sym("unexpected", sym);
				dcl->flags |= ZEND_FFI_DCL_LONG_LONG;
			} else {
				if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_LONG|ZEND_FFI_DCL_SIGNED|ZEND_FFI_DCL_UNSIGNED|ZEND_FFI_DCL_INT|ZEND_FFI_DCL_DOUBLE|ZEND_FFI_DCL_COMPLEX))) yy_error_sym("unexpected", sym);
				dcl->flags |= ZEND_FFI_DCL_LONG;
			}
			sym = get_sym();
			break;
		case YY_FLOAT:
			if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_COMPLEX))) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_FLOAT;
			break;
		case YY_DOUBLE:
			if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_LONG|ZEND_FFI_DCL_COMPLEX))) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_DOUBLE;
			break;
		case YY_SIGNED:
			if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_CHAR|ZEND_FFI_DCL_SHORT|ZEND_FFI_DCL_LONG|ZEND_FFI_DCL_LONG_LONG|ZEND_FFI_DCL_INT))) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_SIGNED;
			break;
		case YY_UNSIGNED:
			if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_CHAR|ZEND_FFI_DCL_SHORT|ZEND_FFI_DCL_LONG|ZEND_FFI_DCL_LONG_LONG|ZEND_FFI_DCL_INT))) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_UNSIGNED;
			break;
		case YY__BOOL:
			if (dcl->flags & ZEND_FFI_DCL_TYPE_SPECIFIERS) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_BOOL;
			break;
		case YY__COMPLEX:
		case YY_COMPLEX:
		case YY___COMPLEX:
		case YY___COMPLEX__:
			if (dcl->flags & (ZEND_FFI_DCL_TYPE_SPECIFIERS-(ZEND_FFI_DCL_FLOAT|ZEND_FFI_DCL_DOUBLE|ZEND_FFI_DCL_LONG))) yy_error_sym("unexpected", sym);
			sym = get_sym();
			dcl->flags |= ZEND_FFI_DCL_COMPLEX;
			break;
		case YY_STRUCT:
		case YY_UNION:
			if (dcl->flags & ZEND_FFI_DCL_TYPE_SPECIFIERS) yy_error_sym("unexpected", sym);
			sym = parse_struct_or_union_specifier(sym, dcl);
			break;
		case YY_ENUM:
			if (dcl->flags & ZEND_FFI_DCL_TYPE_SPECIFIERS) yy_error_sym("unexpected", sym);
			sym = parse_enum_specifier(sym, dcl);
			break;
		case YY_ID:
			if (dcl->flags & ZEND_FFI_DCL_TYPE_SPECIFIERS) yy_error_sym("unexpected", sym);
			/*redeclaration of '%.*s' ??? */
			sym = parse_ID(sym, &name, &name_len);
			dcl->flags |= ZEND_FFI_DCL_TYPEDEF_NAME;
			zend_ffi_resolve_typedef(name, name_len, dcl);
			break;
		default:
			yy_error_sym("unexpected", sym);
	}
	return sym;
}