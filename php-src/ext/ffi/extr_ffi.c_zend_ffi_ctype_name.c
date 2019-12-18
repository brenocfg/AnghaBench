#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tag_name; } ;
struct TYPE_12__ {int /*<<< orphan*/  type; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {int /*<<< orphan*/  ret_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  tag_name; } ;
struct TYPE_14__ {int kind; int attr; TYPE_5__ record; TYPE_4__ array; TYPE_3__ func; TYPE_2__ pointer; TYPE_1__ enumeration; } ;
typedef  TYPE_6__ zend_ffi_type ;
typedef  int /*<<< orphan*/  zend_ffi_ctype_name_buf ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LENGTH_OF_LONG ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 int ZEND_FFI_ATTR_INCOMPLETE_ARRAY ; 
 int ZEND_FFI_ATTR_UNION ; 
 int ZEND_FFI_ATTR_VLA ; 
 TYPE_6__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
#define  ZEND_FFI_TYPE_ARRAY 146 
#define  ZEND_FFI_TYPE_BOOL 145 
#define  ZEND_FFI_TYPE_CHAR 144 
#define  ZEND_FFI_TYPE_DOUBLE 143 
#define  ZEND_FFI_TYPE_ENUM 142 
#define  ZEND_FFI_TYPE_FLOAT 141 
#define  ZEND_FFI_TYPE_FUNC 140 
#define  ZEND_FFI_TYPE_LONGDOUBLE 139 
#define  ZEND_FFI_TYPE_POINTER 138 
#define  ZEND_FFI_TYPE_SINT16 137 
#define  ZEND_FFI_TYPE_SINT32 136 
#define  ZEND_FFI_TYPE_SINT64 135 
#define  ZEND_FFI_TYPE_SINT8 134 
#define  ZEND_FFI_TYPE_STRUCT 133 
#define  ZEND_FFI_TYPE_UINT16 132 
#define  ZEND_FFI_TYPE_UINT32 131 
#define  ZEND_FFI_TYPE_UINT64 130 
#define  ZEND_FFI_TYPE_UINT8 129 
#define  ZEND_FFI_TYPE_VOID 128 
 int ZSTR_LEN (int /*<<< orphan*/ ) ; 
 char const* ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  zend_ffi_ctype_name_append (int /*<<< orphan*/ *,char*,int) ; 
 int zend_ffi_ctype_name_prepend (int /*<<< orphan*/ *,char const*,int) ; 
 char* zend_print_long_to_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zend_ffi_ctype_name(zend_ffi_ctype_name_buf *buf, const zend_ffi_type *type) /* {{{ */
{
	const char *name = NULL;
	int is_ptr = 0;

	while (1) {
		switch (type->kind) {
			case ZEND_FFI_TYPE_VOID:
				name = "void";
				break;
			case ZEND_FFI_TYPE_FLOAT:
				name = "float";
				break;
			case ZEND_FFI_TYPE_DOUBLE:
				name = "double";
				break;
#ifdef HAVE_LONG_DOUBLE
			case ZEND_FFI_TYPE_LONGDOUBLE:
				name = "long double";
				break;
#endif
			case ZEND_FFI_TYPE_UINT8:
				name = "uint8_t";
				break;
			case ZEND_FFI_TYPE_SINT8:
				name = "int8_t";
				break;
			case ZEND_FFI_TYPE_UINT16:
				name = "uint16_t";
				break;
			case ZEND_FFI_TYPE_SINT16:
				name = "int16_t";
				break;
			case ZEND_FFI_TYPE_UINT32:
				name = "uint32_t";
				break;
			case ZEND_FFI_TYPE_SINT32:
				name = "int32_t";
				break;
			case ZEND_FFI_TYPE_UINT64:
				name = "uint64_t";
				break;
			case ZEND_FFI_TYPE_SINT64:
				name = "int64_t";
				break;
			case ZEND_FFI_TYPE_ENUM:
				if (type->enumeration.tag_name) {
					zend_ffi_ctype_name_prepend(buf, ZSTR_VAL(type->enumeration.tag_name), ZSTR_LEN(type->enumeration.tag_name));
				} else {
					zend_ffi_ctype_name_prepend(buf, "<anonymous>", sizeof("<anonymous>")-1);
				}
				name = "enum ";
				break;
			case ZEND_FFI_TYPE_BOOL:
				name = "bool";
				break;
			case ZEND_FFI_TYPE_CHAR:
				name = "char";
				break;
			case ZEND_FFI_TYPE_POINTER:
				if (!zend_ffi_ctype_name_prepend(buf, "*", 1)) {
					return 0;
				}
				is_ptr = 1;
				type = ZEND_FFI_TYPE(type->pointer.type);
				break;
			case ZEND_FFI_TYPE_FUNC:
				if (is_ptr) {
					is_ptr = 0;
					if (!zend_ffi_ctype_name_prepend(buf, "(", 1)
					 || !zend_ffi_ctype_name_append(buf, ")", 1)) {
						return 0;
					}
				}
				if (!zend_ffi_ctype_name_append(buf, "(", 1)
				 || !zend_ffi_ctype_name_append(buf, ")", 1)) {
					return 0;
				}
				type = ZEND_FFI_TYPE(type->func.ret_type);
				break;
			case ZEND_FFI_TYPE_ARRAY:
				if (is_ptr) {
					is_ptr = 0;
					if (!zend_ffi_ctype_name_prepend(buf, "(", 1)
					 || !zend_ffi_ctype_name_append(buf, ")", 1)) {
						return 0;
					}
				}
				if (!zend_ffi_ctype_name_append(buf, "[", 1)) {
					return 0;
				}
				if (type->attr & ZEND_FFI_ATTR_VLA) {
					if (!zend_ffi_ctype_name_append(buf, "*", 1)) {
						return 0;
					}
				} else if (!(type->attr & ZEND_FFI_ATTR_INCOMPLETE_ARRAY)) {
					char str[MAX_LENGTH_OF_LONG + 1];
					char *s = zend_print_long_to_buf(str + sizeof(str) - 1, type->array.length);

					if (!zend_ffi_ctype_name_append(buf, s, strlen(s))) {
						return 0;
					}
				}
				if (!zend_ffi_ctype_name_append(buf, "]", 1)) {
					return 0;
				}
				type = ZEND_FFI_TYPE(type->array.type);
				break;
			case ZEND_FFI_TYPE_STRUCT:
				if (type->attr & ZEND_FFI_ATTR_UNION) {
					if (type->record.tag_name) {
						zend_ffi_ctype_name_prepend(buf, ZSTR_VAL(type->record.tag_name), ZSTR_LEN(type->record.tag_name));
					} else {
						zend_ffi_ctype_name_prepend(buf, "<anonymous>", sizeof("<anonymous>")-1);
					}
					name = "union ";
				} else {
					if (type->record.tag_name) {
						zend_ffi_ctype_name_prepend(buf, ZSTR_VAL(type->record.tag_name), ZSTR_LEN(type->record.tag_name));
					} else {
						zend_ffi_ctype_name_prepend(buf, "<anonymous>", sizeof("<anonymous>")-1);
					}
					name = "struct ";
				}
				break;
			default:
				ZEND_ASSERT(0);
		}
		if (name) {
			break;
		}
	}

//	if (buf->start != buf->end && *buf->start != '[') {
//		if (!zend_ffi_ctype_name_prepend(buf, " ", 1)) {
//			return 0;
//		}
//	}
	return zend_ffi_ctype_name_prepend(buf, name, strlen(name));
}