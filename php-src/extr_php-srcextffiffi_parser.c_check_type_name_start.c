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

/* Variables and functions */
#define  YY_CHAR 157 
#define  YY_COMPLEX 156 
#define  YY_CONST 155 
#define  YY_DOUBLE 154 
#define  YY_ENUM 153 
#define  YY_FLOAT 152 
 int YY_ID ; 
#define  YY_INT 151 
#define  YY_LONG 150 
#define  YY_RESTRICT 149 
#define  YY_SHORT 148 
#define  YY_SIGNED 147 
#define  YY_STRUCT 146 
#define  YY_UNION 145 
#define  YY_UNSIGNED 144 
#define  YY_VOID 143 
#define  YY_VOLATILE 142 
#define  YY__ATOMIC 141 
#define  YY__BOOL 140 
#define  YY__COMPLEX 139 
#define  YY___ATTRIBUTE 138 
#define  YY___ATTRIBUTE__ 137 
#define  YY___COMPLEX 136 
#define  YY___COMPLEX__ 135 
#define  YY___CONST 134 
#define  YY___CONST__ 133 
#define  YY___DECLSPEC 132 
#define  YY___RESTICT 131 
#define  YY___RESTRICT__ 130 
#define  YY___VOLATILE 129 
#define  YY___VOLATILE__ 128 
 int check_ID (int) ; 
 int get_sym () ; 
 scalar_t__ yy_pos ; 
 scalar_t__ yy_text ; 
 scalar_t__ zend_ffi_is_typedef_name (char const*,scalar_t__) ; 

__attribute__((used)) static int check_type_name_start(int sym) {
	if ((sym == YY_ID) && (zend_ffi_is_typedef_name((const char*)yy_text, yy_pos - yy_text))) {
		sym = check_ID(sym);
		if (sym == -1) {
			return -1;
		}
	} else {
		switch (sym) {
			case YY_VOID:
				sym = get_sym();
				break;
			case YY_CHAR:
				sym = get_sym();
				break;
			case YY_SHORT:
				sym = get_sym();
				break;
			case YY_INT:
				sym = get_sym();
				break;
			case YY_LONG:
				sym = get_sym();
				break;
			case YY_FLOAT:
				sym = get_sym();
				break;
			case YY_DOUBLE:
				sym = get_sym();
				break;
			case YY_SIGNED:
				sym = get_sym();
				break;
			case YY_UNSIGNED:
				sym = get_sym();
				break;
			case YY__BOOL:
				sym = get_sym();
				break;
			case YY__COMPLEX:
				sym = get_sym();
				break;
			case YY_COMPLEX:
				sym = get_sym();
				break;
			case YY___COMPLEX:
				sym = get_sym();
				break;
			case YY___COMPLEX__:
				sym = get_sym();
				break;
			case YY_STRUCT:
				sym = get_sym();
				break;
			case YY_UNION:
				sym = get_sym();
				break;
			case YY_ENUM:
				sym = get_sym();
				break;
			case YY_CONST:
				sym = get_sym();
				break;
			case YY___CONST:
				sym = get_sym();
				break;
			case YY___CONST__:
				sym = get_sym();
				break;
			case YY_RESTRICT:
				sym = get_sym();
				break;
			case YY___RESTICT:
				sym = get_sym();
				break;
			case YY___RESTRICT__:
				sym = get_sym();
				break;
			case YY_VOLATILE:
				sym = get_sym();
				break;
			case YY___VOLATILE:
				sym = get_sym();
				break;
			case YY___VOLATILE__:
				sym = get_sym();
				break;
			case YY__ATOMIC:
				sym = get_sym();
				break;
			case YY___ATTRIBUTE:
				sym = get_sym();
				break;
			case YY___ATTRIBUTE__:
				sym = get_sym();
				break;
			case YY___DECLSPEC:
				sym = get_sym();
				break;
			default:
				return -1;
		}
	}
	return sym;
}