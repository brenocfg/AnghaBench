#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  children; void* name; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ xml_element ;
struct buffer_st {int /*<<< orphan*/  offset; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ XMLRPC_VECTOR_TYPE ;
typedef  int XMLRPC_VALUE_TYPE ;
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;
typedef  scalar_t__ XMLRPC_REQUEST_TYPE ;

/* Variables and functions */
 int BUF_SIZE ; 
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELEM_ARRAY ; 
 int /*<<< orphan*/  ELEM_BASE64 ; 
 int /*<<< orphan*/  ELEM_BOOLEAN ; 
 int /*<<< orphan*/  ELEM_DATA ; 
 int /*<<< orphan*/  ELEM_DATETIME ; 
 int /*<<< orphan*/  ELEM_DOUBLE ; 
 int /*<<< orphan*/  ELEM_FAULT ; 
 int /*<<< orphan*/  ELEM_FAULTCODE ; 
 int /*<<< orphan*/  ELEM_INT ; 
 int /*<<< orphan*/  ELEM_MEMBER ; 
 int /*<<< orphan*/  ELEM_NAME ; 
 int /*<<< orphan*/  ELEM_PARAM ; 
 int /*<<< orphan*/  ELEM_PARAMS ; 
 int /*<<< orphan*/  ELEM_STRING ; 
 int /*<<< orphan*/  ELEM_STRUCT ; 
 int /*<<< orphan*/  ELEM_VALUE ; 
 int /*<<< orphan*/  Q_PushTail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  XMLRPC_GetValueBase64 (int /*<<< orphan*/ *) ; 
 int XMLRPC_GetValueBoolean (int /*<<< orphan*/ *) ; 
 char* XMLRPC_GetValueDateTime_ISO8601 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_GetValueDouble (int /*<<< orphan*/ *) ; 
 char* XMLRPC_GetValueID (int /*<<< orphan*/ *) ; 
 int XMLRPC_GetValueInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_GetValueString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_GetValueStringLen (int /*<<< orphan*/ *) ; 
 int XMLRPC_GetValueType (int /*<<< orphan*/ *) ; 
 scalar_t__ XMLRPC_GetVectorType (int /*<<< orphan*/ *) ; 
 scalar_t__ XMLRPC_VectorGetValueWithID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XMLRPC_VectorNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_VectorRewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ap_php_snprintf (char*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base64_encode_xmlrpc (struct buffer_st*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_delete (struct buffer_st*) ; 
 void* estrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  precision ; 
 int /*<<< orphan*/  simplestring_add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  simplestring_addn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 TYPE_1__* xml_elem_new () ; 
#define  xmlrpc_base64 138 
#define  xmlrpc_boolean 137 
#define  xmlrpc_datetime 136 
#define  xmlrpc_double 135 
#define  xmlrpc_empty 134 
#define  xmlrpc_int 133 
 scalar_t__ xmlrpc_request_call ; 
#define  xmlrpc_string 132 
#define  xmlrpc_vector 131 
#define  xmlrpc_vector_array 130 
#define  xmlrpc_vector_mixed 129 
 scalar_t__ xmlrpc_vector_none ; 
#define  xmlrpc_vector_struct 128 

xml_element* XMLRPC_to_xml_element_worker(XMLRPC_VALUE current_vector, XMLRPC_VALUE node,
                                          XMLRPC_REQUEST_TYPE request_type, int depth) {
#define BUF_SIZE 512
   xml_element* root = NULL;
   if (node) {
      char buf[BUF_SIZE];
      XMLRPC_VALUE_TYPE type = XMLRPC_GetValueType(node);
      XMLRPC_VECTOR_TYPE vtype = XMLRPC_GetVectorType(node);
      xml_element* elem_val = xml_elem_new();

      /* special case for when root element is not an array */
      if (depth == 0 &&
          !(type == xmlrpc_vector &&
            vtype == xmlrpc_vector_array &&
            request_type == xmlrpc_request_call) ) {
         int bIsFault = (vtype == xmlrpc_vector_struct && XMLRPC_VectorGetValueWithID(node, ELEM_FAULTCODE));

         xml_element* next_el = XMLRPC_to_xml_element_worker(NULL, node, request_type, depth + 1);
         if (next_el) {
            Q_PushTail(&elem_val->children, next_el);
         }
         elem_val->name = estrdup(bIsFault ? ELEM_FAULT : ELEM_PARAMS);
		}
		else {
         switch (type) {
			case xmlrpc_empty: /*  treat null value as empty string in xmlrpc. */
         case xmlrpc_string:
            elem_val->name = estrdup(ELEM_STRING);
            simplestring_addn(&elem_val->text, XMLRPC_GetValueString(node), XMLRPC_GetValueStringLen(node));
            break;
         case xmlrpc_int:
            elem_val->name = estrdup(ELEM_INT);
            snprintf(buf, BUF_SIZE, "%i", XMLRPC_GetValueInt(node));
            simplestring_add(&elem_val->text, buf);
            break;
         case xmlrpc_boolean:
            elem_val->name = estrdup(ELEM_BOOLEAN);
            snprintf(buf, BUF_SIZE, "%i", XMLRPC_GetValueBoolean(node));
            simplestring_add(&elem_val->text, buf);
            break;
         case xmlrpc_double:
            {
                                elem_val->name = estrdup(ELEM_DOUBLE);
                ap_php_snprintf(buf, BUF_SIZE, "%.*G", (int) EG(precision), XMLRPC_GetValueDouble(node));
                simplestring_add(&elem_val->text, buf);
            }
            break;
         case xmlrpc_datetime:
            elem_val->name = estrdup(ELEM_DATETIME);
            simplestring_add(&elem_val->text, XMLRPC_GetValueDateTime_ISO8601(node));
            break;
         case xmlrpc_base64:
            {
               struct buffer_st buf;
               elem_val->name = estrdup(ELEM_BASE64);
               base64_encode_xmlrpc(&buf, XMLRPC_GetValueBase64(node), XMLRPC_GetValueStringLen(node));
               simplestring_addn(&elem_val->text, buf.data, buf.offset );
               buffer_delete(&buf);
            }
            break;
         case xmlrpc_vector:
            {
               XMLRPC_VECTOR_TYPE my_type = XMLRPC_GetVectorType(node);
               XMLRPC_VALUE xIter = XMLRPC_VectorRewind(node);
               xml_element* root_vector_elem = elem_val;

               switch (my_type) {
               case xmlrpc_vector_array:
                  {
                      if(depth == 0) {
                         elem_val->name = estrdup(ELEM_PARAMS);
                      }
                      else {
                         /* Hi my name is Dave and I like to make things as confusing
                          * as possible, thus I will throw in this 'data' element
                          * where it absolutely does not belong just so that people
                          * cannot code arrays and structs in a similar and straight
                          * forward manner. Have a good day.
                          *
                          * GRRRRRRRRR!
                          */
                         xml_element* data = xml_elem_new();
                         data->name = estrdup(ELEM_DATA);

                         elem_val->name = estrdup(ELEM_ARRAY);
                         Q_PushTail(&elem_val->children, data);
                         root_vector_elem = data;
                      }
                  }
                  break;
               case xmlrpc_vector_mixed:       /* not officially supported */
               case xmlrpc_vector_struct:
                  elem_val->name = estrdup(ELEM_STRUCT);
                  break;
               default:
                  break;
               }

               /* recurse through sub-elements */
               while ( xIter ) {
                  xml_element* next_el = XMLRPC_to_xml_element_worker(node, xIter, request_type, depth + 1);
                  if (next_el) {
                     Q_PushTail(&root_vector_elem->children, next_el);
                  }
                  xIter = XMLRPC_VectorNext(node);
               }
            }
            break;
         default:
            break;
         }
      }

      {
         XMLRPC_VECTOR_TYPE vtype = XMLRPC_GetVectorType(current_vector);

         if (depth == 1) {
            xml_element* value = xml_elem_new();
            value->name = estrdup(ELEM_VALUE);

            /* yet another hack for the "fault" crap */
            if (XMLRPC_VectorGetValueWithID(node, ELEM_FAULTCODE)) {
               root = value;
				}
				else {
               xml_element* param = xml_elem_new();
               param->name = estrdup(ELEM_PARAM);

               Q_PushTail(&param->children, value);

               root = param;
            }
            Q_PushTail(&value->children, elem_val);
			}
			else if (vtype == xmlrpc_vector_struct || vtype == xmlrpc_vector_mixed) {
            xml_element* member = xml_elem_new();
            xml_element* name = xml_elem_new();
            xml_element* value = xml_elem_new();

            member->name = estrdup(ELEM_MEMBER);
            name->name = estrdup(ELEM_NAME);
            value->name = estrdup(ELEM_VALUE);

            simplestring_add(&name->text, XMLRPC_GetValueID(node));

            Q_PushTail(&member->children, name);
            Q_PushTail(&member->children, value);
            Q_PushTail(&value->children, elem_val);

            root = member;
			}
			else if (vtype == xmlrpc_vector_array) {
            xml_element* value = xml_elem_new();

            value->name = estrdup(ELEM_VALUE);

            Q_PushTail(&value->children, elem_val);

            root = value;
			}
			else if (vtype == xmlrpc_vector_none) {
            /* no parent.  non-op */
            root = elem_val;
			}
			else {
            xml_element* value = xml_elem_new();

            value->name = estrdup(ELEM_VALUE);

            Q_PushTail(&value->children, elem_val);

            root = value;
         }
      }
   }
   return root;
}