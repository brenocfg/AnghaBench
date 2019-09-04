#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* key; char* val; } ;
typedef  TYPE_2__ xml_element_attr ;
struct TYPE_5__ {char const* str; int /*<<< orphan*/  len; } ;
struct TYPE_7__ {char const* name; TYPE_1__ text; int /*<<< orphan*/  children; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_3__ xml_element ;
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_ERROR ;

/* Variables and functions */
 void* Q_Head (int /*<<< orphan*/ *) ; 
 void* Q_Next (int /*<<< orphan*/ *) ; 
 scalar_t__ Q_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_AddValueToVector (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_CreateValueString (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XMLRPC_CreateVector (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_VectorAppendString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * describeValue_worker (char const*,char const*,char const*,int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  xi_token_name ; 
 int /*<<< orphan*/  xmlrpc_vector_array ; 
 int /*<<< orphan*/  xmlrpc_vector_mixed ; 
 int /*<<< orphan*/  xmlrpc_vector_struct ; 

XMLRPC_VALUE xml_element_to_method_description(xml_element* el, XMLRPC_ERROR err) {
   XMLRPC_VALUE xReturn = NULL;

   if(el->name) {
      const char* name = NULL;
      const char* type = NULL;
      const char* basetype = NULL;
      const char* desc = NULL;
      const char* def = NULL;
      int optional = 0;
      xml_element_attr* attr_iter = Q_Head(&el->attrs);

      /* grab element attributes up front to save redundant while loops */
      while(attr_iter) {
         if(!strcmp(attr_iter->key, "name")) {
            name = attr_iter->val;
         }
         else if(!strcmp(attr_iter->key, "type")) {
            type = attr_iter->val;
         }
         else if(!strcmp(attr_iter->key, "basetype")) {
            basetype = attr_iter->val;
         }
         else if(!strcmp(attr_iter->key, "desc")) {
            desc = attr_iter->val;
         }
         else if(!strcmp(attr_iter->key, "optional")) {
            if(attr_iter->val && !strcmp(attr_iter->val, "yes")) {
               optional = 1;
            }
         }
         else if(!strcmp(attr_iter->key, "default")) {
            def = attr_iter->val;
         }
         attr_iter = Q_Next(&el->attrs);
      }

      /* value and typeDescription behave about the same */
      if(!strcmp(el->name, "value") || !strcmp(el->name, "typeDescription")) {
         XMLRPC_VALUE xSubList = NULL;
         const char* ptype = !strcmp(el->name, "value") ? type : basetype;
         if(ptype) {
            if(Q_Size(&el->children) &&
               (!strcmp(ptype, "array") || !strcmp(ptype, "struct") || !strcmp(ptype, "mixed"))) {
               xSubList = XMLRPC_CreateVector("member", xmlrpc_vector_array);

               if(xSubList) {
                  xml_element* elem_iter = Q_Head(&el->children);
                  while(elem_iter) {
                     XMLRPC_AddValueToVector(xSubList,
                                             xml_element_to_method_description(elem_iter, err));
                     elem_iter = Q_Next(&el->children);
                  }
               }
            }
            xReturn = describeValue_worker(ptype, name, (desc ? desc : (xSubList ? NULL : el->text.str)), optional, def, xSubList);
         }
      }

      /* these three kids are about equivalent */
      else if(!strcmp(el->name, "params") ||
              !strcmp(el->name, "returns") ||
              !strcmp(el->name, "signature")) {
         if(Q_Size(&el->children)) {
            xml_element* elem_iter = Q_Head(&el->children);
            xReturn = XMLRPC_CreateVector(!strcmp(el->name, "signature") ? NULL : el->name, xmlrpc_vector_struct);


            while(elem_iter) {
               XMLRPC_AddValueToVector(xReturn,
                                       xml_element_to_method_description(elem_iter, err));
               elem_iter = Q_Next(&el->children);
            }
         }
      }


      else if(!strcmp(el->name, "methodDescription")) {
         xml_element* elem_iter = Q_Head(&el->children);
         xReturn = XMLRPC_CreateVector(NULL, xmlrpc_vector_struct);

         XMLRPC_VectorAppendString(xReturn, xi_token_name, name, 0);

         while(elem_iter) {
            XMLRPC_AddValueToVector(xReturn,
                                    xml_element_to_method_description(elem_iter, err));
            elem_iter = Q_Next(&el->children);
         }
      }

      /* items are slightly special */
      else if(!strcmp(el->name, "item")) {
         xReturn = XMLRPC_CreateValueString(name, el->text.str, el->text.len);
      }

      /* sure.  we'll let any ol element with children through */
      else if(Q_Size(&el->children)) {
         xml_element* elem_iter = Q_Head(&el->children);
         xReturn = XMLRPC_CreateVector(el->name, xmlrpc_vector_mixed);

         while(elem_iter) {
            XMLRPC_AddValueToVector(xReturn,
                                    xml_element_to_method_description(elem_iter, err));
            elem_iter = Q_Next(&el->children);
         }
      }

      /* or anything at all really, so long as its got some text.
       * no reason being all snotty about a spec, right?
       */
      else if(el->name && el->text.len) {
         xReturn = XMLRPC_CreateValueString(el->name, el->text.str, el->text.len);
      }
   }

   return xReturn;
}