#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ffi_val ;
struct TYPE_12__ {int flags; } ;
typedef  TYPE_1__ zend_ffi_dcl ;

/* Variables and functions */
#define  YY_AUTO 172 
#define  YY_CHAR 171 
 int /*<<< orphan*/  YY_CHARACTER ; 
#define  YY_COMPLEX 170 
#define  YY_CONST 169 
 int /*<<< orphan*/  YY_DECNUMBER ; 
#define  YY_DOUBLE 168 
#define  YY_ENUM 167 
#define  YY_EXTERN 166 
#define  YY_FLOAT 165 
 int /*<<< orphan*/  YY_FLOATNUMBER ; 
 int /*<<< orphan*/  YY_HEXNUMBER ; 
#define  YY_ID 164 
#define  YY_INLINE 163 
#define  YY_INT 162 
 scalar_t__ YY_IN_SET (int,int,char*) ; 
#define  YY_LONG 161 
 int /*<<< orphan*/  YY_OCTNUMBER ; 
#define  YY_REGISTER 160 
#define  YY_RESTRICT 159 
#define  YY_SHORT 158 
#define  YY_SIGNED 157 
 int /*<<< orphan*/  YY_SIZEOF ; 
#define  YY_STATIC 156 
 int /*<<< orphan*/  YY_STRING ; 
#define  YY_STRUCT 155 
#define  YY_TYPEDEF 154 
#define  YY_UNION 153 
#define  YY_UNSIGNED 152 
#define  YY_VOID 151 
#define  YY_VOLATILE 150 
#define  YY__ALIGNAS 149 
 int /*<<< orphan*/  YY__ALIGNOF ; 
 int /*<<< orphan*/  YY__AND ; 
#define  YY__ATOMIC 148 
 int /*<<< orphan*/  YY__BANG ; 
#define  YY__BOOL 147 
#define  YY__COMPLEX 146 
 int YY__LPAREN ; 
 int /*<<< orphan*/  YY__MINUS ; 
 int /*<<< orphan*/  YY__MINUS_MINUS ; 
#define  YY__NORETURN 145 
 int /*<<< orphan*/  YY__PLUS ; 
 int /*<<< orphan*/  YY__PLUS_PLUS ; 
 int YY__RPAREN ; 
 int /*<<< orphan*/  YY__STAR ; 
 int /*<<< orphan*/  YY__TILDE ; 
 int /*<<< orphan*/  YY___ALIGNOF ; 
 int /*<<< orphan*/  YY___ALIGNOF__ ; 
#define  YY___ATTRIBUTE 144 
#define  YY___ATTRIBUTE__ 143 
#define  YY___CDECL 142 
#define  YY___COMPLEX 141 
#define  YY___COMPLEX__ 140 
#define  YY___CONST 139 
#define  YY___CONST__ 138 
#define  YY___DECLSPEC 137 
 int YY___EXTENSION__ ; 
#define  YY___FASTCALL 136 
#define  YY___INLINE 135 
#define  YY___INLINE__ 134 
#define  YY___RESTRICT 133 
#define  YY___RESTRICT__ 132 
#define  YY___STDCALL 131 
#define  YY___THISCALL 130 
#define  YY___VOLATILE 129 
#define  YY___VOLATILE__ 128 
 int /*<<< orphan*/  ZEND_FFI_ABI_CDECL ; 
 int /*<<< orphan*/  ZEND_FFI_ABI_FASTCALL ; 
 int /*<<< orphan*/  ZEND_FFI_ABI_STDCALL ; 
 int /*<<< orphan*/  ZEND_FFI_ABI_THISCALL ; 
 TYPE_1__ ZEND_FFI_ATTR_INIT ; 
 int ZEND_FFI_DCL_AUTO ; 
 int ZEND_FFI_DCL_EXTERN ; 
 int ZEND_FFI_DCL_INLINE ; 
 int ZEND_FFI_DCL_NO_RETURN ; 
 int ZEND_FFI_DCL_REGISTER ; 
 int ZEND_FFI_DCL_STATIC ; 
 int ZEND_FFI_DCL_STORAGE_CLASS ; 
 int ZEND_FFI_DCL_TYPEDEF ; 
 int ZEND_FFI_DCL_TYPE_SPECIFIERS ; 
 int get_sym () ; 
 int parse_attributes (int,TYPE_1__*) ; 
 int parse_constant_expression (int,int /*<<< orphan*/ *) ; 
 int parse_type_name (int,TYPE_1__*) ; 
 int parse_type_qualifier (int,TYPE_1__*) ; 
 int parse_type_specifier (int,TYPE_1__*) ; 
 int /*<<< orphan*/  synpred_1 (int) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_align_as_type (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ffi_align_as_val (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_set_abi (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_declaration_specifiers(int sym, zend_ffi_dcl *dcl) {
	do {
		switch (sym) {
			case YY_TYPEDEF:
				if (dcl->flags & ZEND_FFI_DCL_STORAGE_CLASS) yy_error_sym("unexpected", sym);
				sym = get_sym();
				dcl->flags |= ZEND_FFI_DCL_TYPEDEF;
				break;
			case YY_EXTERN:
				if (dcl->flags & ZEND_FFI_DCL_STORAGE_CLASS) yy_error_sym("unexpected", sym);
				sym = get_sym();
				dcl->flags |= ZEND_FFI_DCL_EXTERN;
				break;
			case YY_STATIC:
				if (dcl->flags & ZEND_FFI_DCL_STORAGE_CLASS) yy_error_sym("unexpected", sym);
				sym = get_sym();
				dcl->flags |= ZEND_FFI_DCL_STATIC;
				break;
			case YY_AUTO:
				if (dcl->flags & ZEND_FFI_DCL_STORAGE_CLASS) yy_error_sym("unexpected", sym);
				sym = get_sym();
				dcl->flags |= ZEND_FFI_DCL_AUTO;
				break;
			case YY_REGISTER:
				if (dcl->flags & ZEND_FFI_DCL_STORAGE_CLASS) yy_error_sym("unexpected", sym);
				sym = get_sym();
				dcl->flags |= ZEND_FFI_DCL_REGISTER;
				break;
			case YY_INLINE:
			case YY___INLINE:
			case YY___INLINE__:
				sym = get_sym();
				dcl->flags |= ZEND_FFI_DCL_INLINE;
				break;
			case YY__NORETURN:
				sym = get_sym();
				dcl->flags |= ZEND_FFI_DCL_NO_RETURN;
				break;
			case YY___CDECL:
				sym = get_sym();
				zend_ffi_set_abi(dcl, ZEND_FFI_ABI_CDECL);
				break;
			case YY___STDCALL:
				sym = get_sym();
				zend_ffi_set_abi(dcl, ZEND_FFI_ABI_STDCALL);
				break;
			case YY___FASTCALL:
				sym = get_sym();
				zend_ffi_set_abi(dcl, ZEND_FFI_ABI_FASTCALL);
				break;
			case YY___THISCALL:
				sym = get_sym();
				zend_ffi_set_abi(dcl, ZEND_FFI_ABI_THISCALL);
				break;
			case YY__ALIGNAS:
				sym = get_sym();
				if (sym != YY__LPAREN) {
					yy_error_sym("'(' expected, got", sym);
				}
				sym = get_sym();
				if ((YY_IN_SET(sym, (YY___EXTENSION__,YY_VOID,YY_CHAR,YY_SHORT,YY_INT,YY_LONG,YY_FLOAT,YY_DOUBLE,YY_SIGNED,YY_UNSIGNED,YY__BOOL,YY__COMPLEX,YY_COMPLEX,YY___COMPLEX,YY___COMPLEX__,YY_STRUCT,YY_UNION,YY_ENUM,YY_ID,YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC), "\002\000\340\377\377\177\004\007\000\000\000\001\000")) && synpred_1(sym)) {
					zend_ffi_dcl align_dcl = ZEND_FFI_ATTR_INIT;
					sym = parse_type_name(sym, &align_dcl);
					zend_ffi_align_as_type(dcl, &align_dcl);
				} else if (YY_IN_SET(sym, (YY__LPAREN,YY_ID,YY_OCTNUMBER,YY_DECNUMBER,YY_HEXNUMBER,YY_FLOATNUMBER,YY_STRING,YY_CHARACTER,YY__PLUS_PLUS,YY__MINUS_MINUS,YY__AND,YY__STAR,YY__PLUS,YY__MINUS,YY__TILDE,YY__BANG,YY_SIZEOF,YY__ALIGNOF,YY___ALIGNOF,YY___ALIGNOF__), "\010\000\000\000\000\000\020\000\002\214\177\177\000")) {
					zend_ffi_val align_val;
					sym = parse_constant_expression(sym, &align_val);
					zend_ffi_align_as_val(dcl, &align_val);
				} else {
					yy_error_sym("unexpected", sym);
				}
				if (sym != YY__RPAREN) {
					yy_error_sym("')' expected, got", sym);
				}
				sym = get_sym();
				break;
			case YY___ATTRIBUTE:
			case YY___ATTRIBUTE__:
			case YY___DECLSPEC:
				sym = parse_attributes(sym, dcl);
				break;
			case YY_CONST:
			case YY___CONST:
			case YY___CONST__:
			case YY_RESTRICT:
			case YY___RESTRICT:
			case YY___RESTRICT__:
			case YY_VOLATILE:
			case YY___VOLATILE:
			case YY___VOLATILE__:
			case YY__ATOMIC:
				sym = parse_type_qualifier(sym, dcl);
				break;
			case YY_VOID:
			case YY_CHAR:
			case YY_SHORT:
			case YY_INT:
			case YY_LONG:
			case YY_FLOAT:
			case YY_DOUBLE:
			case YY_SIGNED:
			case YY_UNSIGNED:
			case YY__BOOL:
			case YY__COMPLEX:
			case YY_COMPLEX:
			case YY___COMPLEX:
			case YY___COMPLEX__:
			case YY_STRUCT:
			case YY_UNION:
			case YY_ENUM:
			case YY_ID:
				sym = parse_type_specifier(sym, dcl);
				break;
			default:
				yy_error_sym("unexpected", sym);
		}
	} while ((YY_IN_SET(sym, (YY_TYPEDEF,YY_EXTERN,YY_STATIC,YY_AUTO,YY_REGISTER,YY_INLINE,YY___INLINE,YY___INLINE__,YY__NORETURN,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY__ALIGNAS,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY_VOID,YY_CHAR,YY_SHORT,YY_INT,YY_LONG,YY_FLOAT,YY_DOUBLE,YY_SIGNED,YY_UNSIGNED,YY__BOOL,YY__COMPLEX,YY_COMPLEX,YY___COMPLEX,YY___COMPLEX__,YY_STRUCT,YY_UNION,YY_ENUM,YY_ID), "\200\377\377\377\377\177\004\007\000\000\000\001\000")) && (sym != YY_ID || !(dcl->flags & ZEND_FFI_DCL_TYPE_SPECIFIERS)));
	return sym;
}