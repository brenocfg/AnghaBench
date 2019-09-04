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
 int LDOUBLE_SIZE ; 
#define  TOK_CCHAR 140 
#define  TOK_CDOUBLE 139 
#define  TOK_CFLOAT 138 
#define  TOK_CINT 137 
#define  TOK_CLDOUBLE 136 
#define  TOK_CLLONG 135 
#define  TOK_CUINT 134 
#define  TOK_CULLONG 133 
#define  TOK_LCHAR 132 
#define  TOK_LINENUM 131 
#define  TOK_LSTR 130 
#define  TOK_PPNUM 129 
#define  TOK_STR 128 
 int /*<<< orphan*/  tcc_error (char*) ; 

__attribute__((used)) static inline int tok_ext_size(int t)
{
	switch (t) {
	/* 4 bytes */
	case TOK_CINT:
	case TOK_CUINT:
	case TOK_CCHAR:
	case TOK_LCHAR:
	case TOK_CFLOAT:
	case TOK_LINENUM:
		return 1;
	case TOK_STR:
	case TOK_LSTR:
	case TOK_PPNUM:
		tcc_error ("unsupported token");
		return 1;
	case TOK_CDOUBLE:
	case TOK_CLLONG:
	case TOK_CULLONG:
		return 2;
	case TOK_CLDOUBLE:
		return LDOUBLE_SIZE / 4;
	default:
		return 0;
	}
}