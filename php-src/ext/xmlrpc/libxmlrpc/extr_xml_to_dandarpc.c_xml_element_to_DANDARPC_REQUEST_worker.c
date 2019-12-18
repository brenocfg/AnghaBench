#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* key; char* val; } ;
typedef  TYPE_2__ xml_element_attr ;
struct TYPE_7__ {int /*<<< orphan*/  str; int /*<<< orphan*/  len; } ;
struct TYPE_9__ {char const* name; TYPE_1__ text; int /*<<< orphan*/  children; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_3__ xml_element ;
struct buffer_st {int /*<<< orphan*/  offset; int /*<<< orphan*/  data; } ;
typedef  void* XMLRPC_VALUE ;
typedef  scalar_t__ XMLRPC_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ARRAY ; 
 int /*<<< orphan*/  ATTR_BASE64 ; 
 int /*<<< orphan*/  ATTR_BOOLEAN ; 
 int /*<<< orphan*/  ATTR_DATETIME ; 
 int /*<<< orphan*/  ATTR_DOUBLE ; 
 int /*<<< orphan*/  ATTR_ID ; 
 int /*<<< orphan*/  ATTR_INT ; 
 int /*<<< orphan*/  ATTR_MIXED ; 
 int /*<<< orphan*/  ATTR_SCALAR ; 
 int /*<<< orphan*/  ATTR_STRING ; 
 int /*<<< orphan*/  ATTR_STRUCT ; 
 int /*<<< orphan*/  ATTR_TYPE ; 
 int /*<<< orphan*/  ATTR_VECTOR ; 
 int /*<<< orphan*/  ELEM_METHODCALL ; 
 int /*<<< orphan*/  ELEM_METHODNAME ; 
 int /*<<< orphan*/  ELEM_METHODRESPONSE ; 
 TYPE_2__* Q_Head (int /*<<< orphan*/ *) ; 
 TYPE_2__* Q_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_AddValueToVector (void*,void*) ; 
 void* XMLRPC_CreateValueEmpty () ; 
 int /*<<< orphan*/  XMLRPC_RequestSetMethodName (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_RequestSetRequestType (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetIsVector (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueBase64 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueBoolean (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueDateTime_ISO8601 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueDouble (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueID_Case (void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueInt (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueString (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base64_decode_xmlrpc (struct buffer_st*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_delete (struct buffer_st*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlrpc_case_exact ; 
 int /*<<< orphan*/  xmlrpc_request_call ; 
 int /*<<< orphan*/  xmlrpc_request_response ; 
 int /*<<< orphan*/  xmlrpc_vector_array ; 
 int /*<<< orphan*/  xmlrpc_vector_mixed ; 
 int /*<<< orphan*/  xmlrpc_vector_struct ; 

XMLRPC_VALUE xml_element_to_DANDARPC_REQUEST_worker(XMLRPC_REQUEST request, XMLRPC_VALUE xCurrent, xml_element* el) {
   if(!xCurrent) {
      xCurrent = XMLRPC_CreateValueEmpty();
   }

   if(el->name) {
      const char* id = NULL;
      const char* type = NULL;
      xml_element_attr* attr_iter = Q_Head(&el->attrs);

      while(attr_iter) {
         if(!strcmp(attr_iter->key, ATTR_ID)) {
            id = attr_iter->val;
         }
         if(!strcmp(attr_iter->key, ATTR_TYPE)) {
            type = attr_iter->val;
         }
         attr_iter = Q_Next(&el->attrs);
      }

      if(id) {
         XMLRPC_SetValueID_Case(xCurrent, id, 0, xmlrpc_case_exact);
      }

      if(!strcmp(el->name, ATTR_SCALAR)) {
         if(!type || !strcmp(type, ATTR_STRING)) {
            XMLRPC_SetValueString(xCurrent, el->text.str, el->text.len);
         }
         else if(!strcmp(type, ATTR_INT)) {
            XMLRPC_SetValueInt(xCurrent, atoi(el->text.str));
         }
         else if(!strcmp(type, ATTR_BOOLEAN)) {
            XMLRPC_SetValueBoolean(xCurrent, atoi(el->text.str));
         }
         else if(!strcmp(type, ATTR_DOUBLE)) {
            XMLRPC_SetValueDouble(xCurrent, atof(el->text.str));
         }
         else if(!strcmp(type, ATTR_DATETIME)) {
            XMLRPC_SetValueDateTime_ISO8601(xCurrent, el->text.str);
         }
         else if(!strcmp(type, ATTR_BASE64)) {
            struct buffer_st buf;
            base64_decode_xmlrpc(&buf, el->text.str, el->text.len);
            XMLRPC_SetValueBase64(xCurrent, buf.data, buf.offset);
            buffer_delete(&buf);
         }
      }
      else if(!strcmp(el->name, ATTR_VECTOR)) {
         xml_element* iter = (xml_element*)Q_Head(&el->children);

         if(!type || !strcmp(type, ATTR_MIXED)) {
            XMLRPC_SetIsVector(xCurrent, xmlrpc_vector_mixed);
         }
         else if(!strcmp(type, ATTR_ARRAY)) {
				XMLRPC_SetIsVector(xCurrent, xmlrpc_vector_array);
         }
         else if(!strcmp(type, ATTR_STRUCT)) {
            XMLRPC_SetIsVector(xCurrent, xmlrpc_vector_struct);
         }
         while( iter ) {
            XMLRPC_VALUE xNext = XMLRPC_CreateValueEmpty();
            xml_element_to_DANDARPC_REQUEST_worker(request, xNext, iter);
            XMLRPC_AddValueToVector(xCurrent, xNext);
            iter = (xml_element*)Q_Next(&el->children);
         }
      }
      else {
         xml_element* iter = (xml_element*)Q_Head(&el->children);
         while( iter ) {
            xml_element_to_DANDARPC_REQUEST_worker(request, xCurrent, iter);
            iter = (xml_element*)Q_Next(&el->children);
         }

         if(!strcmp(el->name, ELEM_METHODCALL)) {
            if(request) {
               XMLRPC_RequestSetRequestType(request, xmlrpc_request_call);
            }
         }
         else if(!strcmp(el->name, ELEM_METHODRESPONSE)) {
            if(request) {
               XMLRPC_RequestSetRequestType(request, xmlrpc_request_response);
            }
         }
         else if(!strcmp(el->name, ELEM_METHODNAME)) {
            if(request) {
               XMLRPC_RequestSetMethodName(request, el->text.str);
            }
         }
      }
   }
   return xCurrent;
}