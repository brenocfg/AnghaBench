#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  attrs; int /*<<< orphan*/  text; int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ xml_element_attr ;
typedef  TYPE_1__ xml_element ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct buffer_st {int /*<<< orphan*/  offset; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int XMLRPC_VALUE_TYPE_EASY ;
typedef  scalar_t__ XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  Q_PushTail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* TOKEN_ARRAY ; 
 int /*<<< orphan*/  TOKEN_ARRAY_TYPE ; 
 char* TOKEN_BASE64 ; 
 char* TOKEN_BOOLEAN ; 
 char* TOKEN_DATETIME ; 
 char* TOKEN_DOUBLE ; 
 char* TOKEN_FAULT ; 
 char* TOKEN_INT ; 
 char* TOKEN_NULL ; 
 char* TOKEN_STRING ; 
 int /*<<< orphan*/  TOKEN_TYPE ; 
 int /*<<< orphan*/  XMLRPC_CleanupValue (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueBase64 (scalar_t__) ; 
 int XMLRPC_GetValueBoolean (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueDateTime (scalar_t__) ; 
 double XMLRPC_GetValueDouble (scalar_t__) ; 
 scalar_t__ XMLRPC_GetValueID (scalar_t__) ; 
 int XMLRPC_GetValueInt (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueString (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueStringLen (scalar_t__) ; 
 int XMLRPC_GetValueTypeEasy (scalar_t__) ; 
 scalar_t__ XMLRPC_VectorNext (scalar_t__) ; 
 scalar_t__ XMLRPC_VectorRewind (scalar_t__) ; 
 int XMLRPC_VectorSize (scalar_t__) ; 
 int /*<<< orphan*/  base64_encode_xmlrpc (struct buffer_st*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_delete (struct buffer_st*) ; 
 int /*<<< orphan*/  estrdup (char*) ; 
 scalar_t__ gen_fault_xmlrpc (scalar_t__,TYPE_1__*) ; 
 char* get_array_soap_type (scalar_t__) ; 
 int get_fault_type (scalar_t__) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 TYPE_1__* new_attr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  simplestring_add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  simplestring_addn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 TYPE_1__* xml_elem_new () ; 
#define  xmlrpc_type_array 137 
#define  xmlrpc_type_base64 136 
#define  xmlrpc_type_boolean 135 
#define  xmlrpc_type_datetime 134 
#define  xmlrpc_type_double 133 
#define  xmlrpc_type_empty 132 
#define  xmlrpc_type_int 131 
#define  xmlrpc_type_mixed 130 
#define  xmlrpc_type_string 129 
#define  xmlrpc_type_struct 128 

xml_element* SOAP_to_xml_element_worker(XMLRPC_REQUEST request, XMLRPC_VALUE node) {
#define BUF_SIZE 128
	xml_element* elem_val = NULL;
	if (node) {
		int bFreeNode = 0;  /* sometimes we may need to free 'node' variable */
		char buf[BUF_SIZE];
		XMLRPC_VALUE_TYPE_EASY type = XMLRPC_GetValueTypeEasy(node);
		char* pName = NULL, *pAttrType = NULL;

		/* create our return value element */
		elem_val = xml_elem_new();

		switch (type) {
		case xmlrpc_type_struct:
		case xmlrpc_type_mixed:
		case xmlrpc_type_array:
			if (type == xmlrpc_type_array) {
				/* array's are _very_ special in soap.
				   TODO: Should handle sparse/partial arrays here. */

				/* determine soap array type. */
				const char* type = get_array_soap_type(node);
				xml_element_attr* attr_array_type = NULL;

				/* specify array kids type and array size. */
				snprintf(buf, sizeof(buf), "%s[%i]", type, XMLRPC_VectorSize(node));
				attr_array_type = new_attr(TOKEN_ARRAY_TYPE, buf);

				Q_PushTail(&elem_val->attrs, attr_array_type);

				pAttrType = TOKEN_ARRAY;
			}
			/* check for fault, which is a rather special case.
			   (can't these people design anything consistent/simple/elegant?) */
			else if (type == xmlrpc_type_struct) {
				int fault_type = get_fault_type(node);
				if (fault_type) {
					if (fault_type == 1) {
						/* gen fault from xmlrpc style fault codes
						    notice that we get a new node, which must be freed herein. */
						node = gen_fault_xmlrpc(node, elem_val);
						bFreeNode = 1;
					}
					pName = TOKEN_FAULT;
				}
			}

			{
				/* recurse through sub-elements */
				XMLRPC_VALUE xIter = XMLRPC_VectorRewind(node);
				while ( xIter ) {
					xml_element* next_el = SOAP_to_xml_element_worker(request, xIter);
					if (next_el) {
						Q_PushTail(&elem_val->children, next_el);
					}
					xIter = XMLRPC_VectorNext(node);
				}
			}

			break;

			/* handle scalar types */
		case xmlrpc_type_empty:
			pAttrType = TOKEN_NULL;
			break;
		case xmlrpc_type_string:
			pAttrType = TOKEN_STRING;
			simplestring_addn(&elem_val->text, XMLRPC_GetValueString(node), XMLRPC_GetValueStringLen(node));
			break;
		case xmlrpc_type_int:
			pAttrType = TOKEN_INT;
			snprintf(buf, BUF_SIZE, "%i", XMLRPC_GetValueInt(node));
			simplestring_add(&elem_val->text, buf);
			break;
		case xmlrpc_type_boolean:
			pAttrType = TOKEN_BOOLEAN;
			snprintf(buf, BUF_SIZE, "%i", XMLRPC_GetValueBoolean(node));
			simplestring_add(&elem_val->text, buf);
			break;
		case xmlrpc_type_double:
			pAttrType = TOKEN_DOUBLE;
			snprintf(buf, BUF_SIZE, "%f", XMLRPC_GetValueDouble(node));
			simplestring_add(&elem_val->text, buf);
			break;
		case xmlrpc_type_datetime:
			{
				time_t tt = XMLRPC_GetValueDateTime(node);
				struct tm *tm = localtime (&tt);
				pAttrType = TOKEN_DATETIME;
				if(strftime (buf, BUF_SIZE, "%Y-%m-%dT%H:%M:%SZ", tm)) {
					simplestring_add(&elem_val->text, buf);
				}
			}
			break;
		case xmlrpc_type_base64:
			{
				struct buffer_st buf;
				pAttrType = TOKEN_BASE64;
				base64_encode_xmlrpc(&buf, XMLRPC_GetValueBase64(node), XMLRPC_GetValueStringLen(node));
				simplestring_addn(&elem_val->text, buf.data, buf.offset );
				buffer_delete(&buf);
			}
			break;
			break;
		default:
			break;
		}

		/* determining element's name is a bit tricky, due to soap semantics. */
		if (!pName) {
			/* if the value's type is known... */
			if (pAttrType) {
				/* see if it has an id (key). If so, use that as name, and type as an attribute. */
				pName = (char*)XMLRPC_GetValueID(node);
				if (pName) {
					Q_PushTail(&elem_val->attrs, new_attr(TOKEN_TYPE, pAttrType));
				}

				/* otherwise, use the type as the name. */
				else {
					pName = pAttrType;
				}
			}
			/* if the value's type is not known... (a rare case?) */
			else {
				/* see if it has an id (key). otherwise, default to generic "item" */
				pName = (char*)XMLRPC_GetValueID(node);
				if (!pName) {
					pName = "item";
				}
			}
		}
		elem_val->name = estrdup(pName);

		/* cleanup */
		if (bFreeNode) {
			XMLRPC_CleanupValue(node);
		}
	}
	return elem_val;
}