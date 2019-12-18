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
struct TYPE_4__ {int /*<<< orphan*/  str; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int /*<<< orphan*/  children; TYPE_1__ text; scalar_t__ name; } ;
typedef  TYPE_2__ xml_element ;
struct buffer_st {int /*<<< orphan*/  offset; int /*<<< orphan*/  data; } ;
typedef  void* XMLRPC_VALUE ;
typedef  scalar_t__ XMLRPC_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  ELEM_BASE64 ; 
 int /*<<< orphan*/  ELEM_BOOLEAN ; 
 int /*<<< orphan*/  ELEM_DATA ; 
 int /*<<< orphan*/  ELEM_DATETIME ; 
 int /*<<< orphan*/  ELEM_DOUBLE ; 
 int /*<<< orphan*/  ELEM_FAULT ; 
 int /*<<< orphan*/  ELEM_I4 ; 
 int /*<<< orphan*/  ELEM_INT ; 
 int /*<<< orphan*/  ELEM_METHODCALL ; 
 int /*<<< orphan*/  ELEM_METHODNAME ; 
 int /*<<< orphan*/  ELEM_METHODRESPONSE ; 
 int /*<<< orphan*/  ELEM_NAME ; 
 int /*<<< orphan*/  ELEM_PARAMS ; 
 int /*<<< orphan*/  ELEM_STRING ; 
 int /*<<< orphan*/  ELEM_STRUCT ; 
 int /*<<< orphan*/  ELEM_VALUE ; 
 scalar_t__ Q_Head (int /*<<< orphan*/ *) ; 
 scalar_t__ Q_Next (int /*<<< orphan*/ *) ; 
 scalar_t__ Q_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_AddValueToVector (void*,void*) ; 
 void* XMLRPC_CreateValueEmpty () ; 
 scalar_t__ XMLRPC_RequestGetRequestType (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_RequestSetMethodName (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_RequestSetRequestType (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_SetIsVector (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueBase64 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueBoolean (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueDateTime_ISO8601 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueDouble (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueID_Case (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueInt (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueString (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base64_decode_xmlrpc (struct buffer_st*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_delete (struct buffer_st*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlrpc_case_exact ; 
 scalar_t__ xmlrpc_request_call ; 
 scalar_t__ xmlrpc_request_response ; 
 int /*<<< orphan*/  xmlrpc_vector_array ; 
 int /*<<< orphan*/  xmlrpc_vector_struct ; 

XMLRPC_VALUE xml_element_to_XMLRPC_REQUEST_worker(XMLRPC_REQUEST request, XMLRPC_VALUE parent_vector, XMLRPC_VALUE current_val, xml_element* el) {
   if (!current_val) {
      /* This should only be the case for the first element */
      current_val = XMLRPC_CreateValueEmpty();
   }

	if (el->name) {

      /* first, deal with the crazy/stupid fault format */
      if (!strcmp(el->name, ELEM_FAULT)) {
			xml_element* fault_value = (xml_element*)Q_Head(&el->children);
			XMLRPC_SetIsVector(current_val, xmlrpc_vector_struct);

         if(fault_value) {
            xml_element* fault_struct = (xml_element*)Q_Head(&fault_value->children);
            if(fault_struct) {
               xml_element* iter = (xml_element*)Q_Head(&fault_struct->children);

               while (iter) {
                  XMLRPC_VALUE xNextVal = XMLRPC_CreateValueEmpty();
                  xml_element_to_XMLRPC_REQUEST_worker(request, current_val, xNextVal, iter);
                  XMLRPC_AddValueToVector(current_val, xNextVal);
                  iter = (xml_element*)Q_Next(&fault_struct->children);
               }
            }
         }
      }
		else if (!strcmp(el->name, ELEM_DATA)	/* should be ELEM_ARRAY, but there is an extra level. weird */
			 || (!strcmp(el->name, ELEM_PARAMS) &&
				  (XMLRPC_RequestGetRequestType(request) == xmlrpc_request_call)) ) {		/* this "PARAMS" concept is silly.  dave?! */
         xml_element* iter = (xml_element*)Q_Head(&el->children);
         XMLRPC_SetIsVector(current_val, xmlrpc_vector_array);

         while (iter) {
            XMLRPC_VALUE xNextVal = XMLRPC_CreateValueEmpty();
            xml_element_to_XMLRPC_REQUEST_worker(request, current_val, xNextVal, iter);
            XMLRPC_AddValueToVector(current_val, xNextVal);
            iter = (xml_element*)Q_Next(&el->children);
         }
		}
		else if (!strcmp(el->name, ELEM_STRUCT)) {
         xml_element* iter = (xml_element*)Q_Head(&el->children);
         XMLRPC_SetIsVector(current_val, xmlrpc_vector_struct);

         while ( iter ) {
            XMLRPC_VALUE xNextVal = XMLRPC_CreateValueEmpty();
            xml_element_to_XMLRPC_REQUEST_worker(request, current_val, xNextVal, iter);
            XMLRPC_AddValueToVector(current_val, xNextVal);
            iter = (xml_element*)Q_Next(&el->children);
         }
		}
		else if (!strcmp(el->name, ELEM_STRING) ||
                 (!strcmp(el->name, ELEM_VALUE) && Q_Size(&el->children) == 0)) {
         XMLRPC_SetValueString(current_val, el->text.str, el->text.len);
		}
		else if (!strcmp(el->name, ELEM_NAME)) {
         XMLRPC_SetValueID_Case(current_val, el->text.str, 0, xmlrpc_case_exact);
		}
		else if (!strcmp(el->name, ELEM_INT) || !strcmp(el->name, ELEM_I4)) {
         XMLRPC_SetValueInt(current_val, atoi(el->text.str));
		}
		else if (!strcmp(el->name, ELEM_BOOLEAN)) {
         XMLRPC_SetValueBoolean(current_val, atoi(el->text.str));
		}
		else if (!strcmp(el->name, ELEM_DOUBLE)) {
         XMLRPC_SetValueDouble(current_val, atof(el->text.str));
		}
		else if (!strcmp(el->name, ELEM_DATETIME)) {
         XMLRPC_SetValueDateTime_ISO8601(current_val, el->text.str);
		}
		else if (!strcmp(el->name, ELEM_BASE64)) {
         struct buffer_st buf;
         base64_decode_xmlrpc(&buf, el->text.str, el->text.len);
         XMLRPC_SetValueBase64(current_val, buf.data, buf.offset);
         buffer_delete(&buf);
		}
		else {
         xml_element* iter;

         if (!strcmp(el->name, ELEM_METHODCALL)) {
            if (request) {
               XMLRPC_RequestSetRequestType(request, xmlrpc_request_call);
            }
			}
			else if (!strcmp(el->name, ELEM_METHODRESPONSE)) {
            if (request) {
               XMLRPC_RequestSetRequestType(request, xmlrpc_request_response);
            }
			}
			else if (!strcmp(el->name, ELEM_METHODNAME)) {
            if (request) {
               XMLRPC_RequestSetMethodName(request, el->text.str);
            }
         }

         iter = (xml_element*)Q_Head(&el->children);
         while ( iter ) {
            xml_element_to_XMLRPC_REQUEST_worker(request, parent_vector,
                                                 current_val, iter);
            iter = (xml_element*)Q_Next(&el->children);
         }
      }
   }
   return current_val;
}