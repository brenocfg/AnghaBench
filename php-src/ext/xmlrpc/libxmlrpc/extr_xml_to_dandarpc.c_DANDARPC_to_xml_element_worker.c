#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* val; int /*<<< orphan*/  children; int /*<<< orphan*/  text; int /*<<< orphan*/  attrs; void* key; void* name; } ;
typedef  TYPE_2__ xml_element_attr ;
typedef  TYPE_2__ xml_element ;
struct buffer_st {int /*<<< orphan*/  offset; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  XMLRPC_VECTOR_TYPE ;
typedef  int XMLRPC_VALUE_TYPE ;
typedef  scalar_t__ XMLRPC_VALUE ;
typedef  TYPE_4__* XMLRPC_REQUEST_OUTPUT_OPTIONS ;
typedef  scalar_t__ XMLRPC_REQUEST ;
struct TYPE_10__ {scalar_t__ verbosity; } ;
struct TYPE_12__ {TYPE_1__ xml_elem_opts; } ;

/* Variables and functions */
 char* ATTR_ARRAY ; 
 char* ATTR_BASE64 ; 
 char* ATTR_BOOLEAN ; 
 char* ATTR_DATETIME ; 
 char* ATTR_DOUBLE ; 
 char const* ATTR_ID ; 
 char* ATTR_INT ; 
 char* ATTR_MIXED ; 
 char const* ATTR_SCALAR ; 
 char* ATTR_STRING ; 
 char* ATTR_STRUCT ; 
 char const* ATTR_TYPE ; 
 char const* ATTR_VECTOR ; 
 int BUF_SIZE ; 
 int /*<<< orphan*/  Q_PushTail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  XMLRPC_GetValueBase64 (scalar_t__) ; 
 int XMLRPC_GetValueBoolean (scalar_t__) ; 
 char* XMLRPC_GetValueDateTime_ISO8601 (scalar_t__) ; 
 double XMLRPC_GetValueDouble (scalar_t__) ; 
 char* XMLRPC_GetValueID (scalar_t__) ; 
 int XMLRPC_GetValueInt (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueString (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueStringLen (scalar_t__) ; 
 int XMLRPC_GetValueType (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetVectorType (scalar_t__) ; 
 TYPE_4__* XMLRPC_RequestGetOutputOptions (scalar_t__) ; 
 scalar_t__ XMLRPC_VectorNext (scalar_t__) ; 
 scalar_t__ XMLRPC_VectorRewind (scalar_t__) ; 
 int /*<<< orphan*/  base64_encode_xmlrpc (struct buffer_st*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_delete (struct buffer_st*) ; 
 TYPE_2__* emalloc (int) ; 
 void* estrdup (char const*) ; 
 int /*<<< orphan*/  simplestring_add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  simplestring_addn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double) ; 
 TYPE_2__* xml_elem_new () ; 
 scalar_t__ xml_elem_no_white_space ; 
#define  xmlrpc_base64 137 
#define  xmlrpc_boolean 136 
#define  xmlrpc_datetime 135 
#define  xmlrpc_double 134 
#define  xmlrpc_int 133 
#define  xmlrpc_string 132 
#define  xmlrpc_vector 131 
#define  xmlrpc_vector_array 130 
#define  xmlrpc_vector_mixed 129 
#define  xmlrpc_vector_struct 128 

xml_element* DANDARPC_to_xml_element_worker(XMLRPC_REQUEST request, XMLRPC_VALUE node) {
#define BUF_SIZE 512
   xml_element* root = NULL;
   if(node) {
      char buf[BUF_SIZE];
      const char* id = XMLRPC_GetValueID(node);
      XMLRPC_VALUE_TYPE type = XMLRPC_GetValueType(node);
      XMLRPC_REQUEST_OUTPUT_OPTIONS output = XMLRPC_RequestGetOutputOptions(request);
      int bNoAddType = (type == xmlrpc_string && request && output && output->xml_elem_opts.verbosity == xml_elem_no_white_space);
      xml_element* elem_val = xml_elem_new();
      const char* pAttrType = NULL;

      xml_element_attr* attr_type = bNoAddType ? NULL : emalloc(sizeof(xml_element_attr));

      if(attr_type) {
         attr_type->key = estrdup(ATTR_TYPE);
         attr_type->val = 0;
         Q_PushTail(&elem_val->attrs, attr_type);
      }

      elem_val->name = (type == xmlrpc_vector) ? estrdup(ATTR_VECTOR) : estrdup(ATTR_SCALAR);

      if(id && *id) {
         xml_element_attr* attr_id = emalloc(sizeof(xml_element_attr));
         if(attr_id) {
            attr_id->key = estrdup(ATTR_ID);
            attr_id->val = estrdup(id);
            Q_PushTail(&elem_val->attrs, attr_id);
         }
      }

      switch(type) {
         case xmlrpc_string:
            pAttrType = ATTR_STRING;
            simplestring_addn(&elem_val->text, XMLRPC_GetValueString(node), XMLRPC_GetValueStringLen(node));
            break;
         case xmlrpc_int:
            pAttrType = ATTR_INT;
            snprintf(buf, BUF_SIZE, "%i", XMLRPC_GetValueInt(node));
            simplestring_add(&elem_val->text, buf);
            break;
         case xmlrpc_boolean:
            pAttrType = ATTR_BOOLEAN;
            snprintf(buf, BUF_SIZE, "%i", XMLRPC_GetValueBoolean(node));
            simplestring_add(&elem_val->text, buf);
            break;
         case xmlrpc_double:
            pAttrType = ATTR_DOUBLE;
            snprintf(buf, BUF_SIZE, "%f", XMLRPC_GetValueDouble(node));
            simplestring_add(&elem_val->text, buf);
            break;
         case xmlrpc_datetime:
            pAttrType = ATTR_DATETIME;
            simplestring_add(&elem_val->text, XMLRPC_GetValueDateTime_ISO8601(node));
            break;
         case xmlrpc_base64:
            {
               struct buffer_st buf;
               pAttrType = ATTR_BASE64;
               base64_encode_xmlrpc(&buf, XMLRPC_GetValueBase64(node), XMLRPC_GetValueStringLen(node));
               simplestring_addn(&elem_val->text, buf.data, buf.offset );
               buffer_delete(&buf);
            }
            break;
         case xmlrpc_vector:
            {
               XMLRPC_VECTOR_TYPE my_type = XMLRPC_GetVectorType(node);
               XMLRPC_VALUE xIter = XMLRPC_VectorRewind(node);

               switch(my_type) {
                  case xmlrpc_vector_array:
                     pAttrType = ATTR_ARRAY;
                     break;
                  case xmlrpc_vector_mixed:
                     pAttrType = ATTR_MIXED;
                     break;
                  case xmlrpc_vector_struct:
                     pAttrType = ATTR_STRUCT;
                     break;
                  default:
                     break;
               }

               /* recurse through sub-elements */
               while( xIter ) {
                  xml_element* next_el = DANDARPC_to_xml_element_worker(request, xIter);
                  if(next_el) {
                     Q_PushTail(&elem_val->children, next_el);
                  }
                  xIter = XMLRPC_VectorNext(node);
               }
            }
            break;
         default:
            break;
      }
      if(pAttrType && attr_type && !bNoAddType) {
         attr_type->val = estrdup(pAttrType);
      }
      root = elem_val;
   }
   return root;
}