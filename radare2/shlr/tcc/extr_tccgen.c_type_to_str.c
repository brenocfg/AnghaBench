#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf1 ;
struct TYPE_5__ {int t; TYPE_1__* ref; } ;
struct TYPE_4__ {int v; TYPE_2__ type; struct TYPE_4__* next; } ;
typedef  TYPE_1__ Sym ;
typedef  TYPE_2__ CType ;

/* Variables and functions */
 int SYM_FIRST_ANOM ; 
 int SYM_STRUCT ; 
 int VT_ARRAY ; 
#define  VT_BOOL 142 
 int VT_BTYPE ; 
 int VT_CHAR ; 
 int VT_CONSTANT ; 
#define  VT_DOUBLE 141 
#define  VT_ENUM 140 
#define  VT_FLOAT 139 
#define  VT_FUNC 138 
#define  VT_INT16 137 
#define  VT_INT32 136 
#define  VT_INT64 135 
#define  VT_INT8 134 
#define  VT_LDOUBLE 133 
#define  VT_LONG 132 
#define  VT_PTR 131 
#define  VT_STRUCT 130 
 int VT_TYPE ; 
#define  VT_UNION 129 
 int VT_UNSIGNED ; 
#define  VT_VOID 128 
 int VT_VOLATILE ; 
 char const* get_tok_str (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pstrcat (char*,int,char const*) ; 
 int /*<<< orphan*/  pstrcpy (char*,int,char*) ; 
 int /*<<< orphan*/  strcat_printf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void type_to_str(char *buf, int buf_size, CType *type, const char *varstr) {
	int bt, v, t;
	Sym *s, *sa;
	char buf1[256];
	const char *tstr;
	t = type->t & VT_TYPE;
	bt = t & VT_BTYPE;
	buf[0] = '\0';
	if (t & VT_CONSTANT) {
		pstrcat (buf, buf_size, "const ");
	}
	if (t & VT_VOLATILE) {
		pstrcat (buf, buf_size, "volatile ");
	}
	switch (bt) {
	case VT_VOID:
		tstr = "void";
		goto add_tstr;
	case VT_BOOL:
		tstr = "bool";
		goto add_tstr;
	case VT_INT8:
		if (t & VT_UNSIGNED) {
			tstr = "uint8_t";
		} else {
			if (t & VT_CHAR) {
				tstr = "char";
			} else {
				tstr = "int8_t";
			}
		}
		goto add_tstr;
	case VT_INT16:
		if (t & VT_UNSIGNED) {
			tstr = "uint16_t";
		} else {
			tstr = "int16_t";
		}
		goto add_tstr;
	case VT_INT32:
		if (t & VT_UNSIGNED) {
			tstr = "uint32_t";
		} else {
			tstr = "int32_t";
		}
		goto add_tstr;
	case VT_LONG:
		tstr = "long";
		goto add_tstr;
	case VT_INT64:
		if (t & VT_UNSIGNED) {
			tstr = "uint64_t";
		} else {
			tstr = "int64_t";
		}
		goto add_tstr;
	case VT_FLOAT:
		tstr = "float";
		goto add_tstr;
	case VT_DOUBLE:
		tstr = "double";
		goto add_tstr;
	case VT_LDOUBLE:
		tstr = "long double";
add_tstr:
		pstrcat (buf, buf_size, tstr);
		if ((t & VT_UNSIGNED) && (bt != VT_INT8) &&
		    (bt != VT_INT16) && (bt != VT_INT32) &&
		    (bt != VT_INT64)) {
			pstrcat (buf, buf_size, "unsigned ");
		}
		break;
	case VT_ENUM:
	case VT_STRUCT:
	case VT_UNION:
		if (bt == VT_STRUCT) {
			tstr = "struct ";
		} else if (bt == VT_UNION) {
			tstr = "union ";
		} else {
			tstr = "enum ";
		}
		pstrcat (buf, buf_size, tstr);
		v = type->ref->v & ~SYM_STRUCT;
		if (v >= SYM_FIRST_ANOM) {
			strcat_printf (buf, buf_size, "%u", v - SYM_FIRST_ANOM);
		} else {
			pstrcat (buf, buf_size, get_tok_str (v, NULL));
		}
		break;
	case VT_FUNC:
		s = type->ref;
		type_to_str (buf, buf_size, &s->type, varstr);
		pstrcat (buf, buf_size, "(");
		sa = s->next;
		while (sa != NULL) {
			type_to_str (buf1, sizeof(buf1), &sa->type, NULL);
			pstrcat (buf, buf_size, buf1);
			sa = sa->next;
			if (sa) {
				pstrcat (buf, buf_size, ", ");
			}
		}
		pstrcat (buf, buf_size, ")");
		goto no_var;
	case VT_PTR:
		s = type->ref;
		if (t & VT_ARRAY) {
			type_to_str (buf, buf_size, &s->type, NULL);
		} else {
			pstrcpy (buf1, sizeof(buf1), "*");
			if (varstr) {
				pstrcat (buf1, sizeof(buf1), varstr);
			}
			type_to_str (buf, buf_size, &s->type, buf1);
		}
		goto no_var;
	}
	if (varstr) {
		pstrcat (buf, buf_size, " ");
		pstrcat (buf, buf_size, varstr);
	}
no_var:
	;
}