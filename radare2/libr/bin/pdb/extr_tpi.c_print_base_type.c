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
typedef  int EBASE_TYPES ;

/* Variables and functions */
#define  eT_32PINT4 153 
#define  eT_32PLONG 152 
#define  eT_32PRCHAR 151 
#define  eT_32PUCHAR 150 
#define  eT_32PULONG 149 
#define  eT_32PUQUAD 148 
#define  eT_32PUSHORT 147 
#define  eT_32PVOID 146 
#define  eT_32PWCHAR 145 
#define  eT_64PVOID 144 
#define  eT_INT4 143 
#define  eT_INT8 142 
#define  eT_LONG 141 
#define  eT_QUAD 140 
#define  eT_RCHAR 139 
#define  eT_REAL32 138 
#define  eT_REAL64 137 
#define  eT_REAL80 136 
#define  eT_SHORT 135 
#define  eT_UCHAR 134 
#define  eT_UINT4 133 
#define  eT_ULONG 132 
#define  eT_UQUAD 131 
#define  eT_USHORT 130 
#define  eT_VOID 129 
#define  eT_WCHAR 128 

__attribute__((used)) static void print_base_type(EBASE_TYPES base_type, char **name) {
	switch (base_type) {
	case eT_32PINT4:
		*name = "pointer to long";
		break;
	case eT_32PRCHAR:
		*name = "pointer to unsigned char";
		break;
	case eT_32PUCHAR:
		*name = "pointer to unsigned char";
		break;
	case eT_32PULONG:
		*name = "pointer to unsigned long";
		break;
	case eT_32PLONG:
		*name = "pointer to long";
		break;
	case eT_32PUQUAD:
		*name = "pointer to unsigned long long";
		break;
	case eT_32PUSHORT:
		*name = "pointer to unsigned short";
		break;
	case eT_32PVOID:
		*name = "pointer to void";
		break;
	case eT_64PVOID:
		*name = "pointer64 to void";
		break;
	case eT_INT4:
		*name = "long";
		break;
	case eT_INT8:
		*name = "long long";
		break;
	case eT_LONG:
		*name = "long";
		break;
	case eT_QUAD:
		*name = "long long";
		break;
	case eT_RCHAR:
		*name = "unsigned char";
		break;
	case eT_REAL32:
		*name = "float";
		break;
	case eT_REAL64:
		*name = "double";
		break;
	case eT_REAL80:
		*name = "long double";
		break;
	case eT_SHORT:
		*name = "short";
		break;
	case eT_UCHAR:
		*name = "unsigned char";
		break;
	case eT_UINT4:
		*name = "unsigned long";
		break;
	case eT_ULONG:
		*name = "unsigned long";
		break;
	case eT_UQUAD:
		*name = "unsigned long long";
		break;
	case eT_USHORT:
		*name = "unsigned short";
		break;
	case eT_WCHAR:
		*name = "wchar";
		break;
	case eT_VOID:
		*name = "void";
		break;
	case eT_32PWCHAR:
		*name = "pointer to wchar";
		break;
	default:
		*name = "unsupported base type";
		break;
	}
}