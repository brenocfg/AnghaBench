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
struct TYPE_8__ {int /*<<< orphan*/  children; int /*<<< orphan*/  text; void* name; int /*<<< orphan*/  attrs; void* val; void* key; } ;
typedef  TYPE_1__ xml_element_attr ;
typedef  TYPE_1__ xml_element ;
typedef  scalar_t__ XMLRPC_REQUEST_TYPE ;
typedef  scalar_t__ XMLRPC_REQUEST ;

/* Variables and functions */
 char const* ATTR_VERSION ; 
 TYPE_1__* DANDARPC_to_xml_element_worker (scalar_t__,int /*<<< orphan*/ ) ; 
 char* ELEM_METHODCALL ; 
 char const* ELEM_METHODNAME ; 
 char* ELEM_METHODRESPONSE ; 
 char const* ELEM_ROOT ; 
 int /*<<< orphan*/  Q_PushTail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char const* VAL_VERSION_0_9 ; 
 int /*<<< orphan*/  XMLRPC_RequestGetData (scalar_t__) ; 
 char* XMLRPC_RequestGetMethodName (scalar_t__) ; 
 scalar_t__ XMLRPC_RequestGetRequestType (scalar_t__) ; 
 TYPE_1__* emalloc (int) ; 
 void* estrdup (char const*) ; 
 int /*<<< orphan*/  simplestring_add (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* xml_elem_new () ; 
 scalar_t__ xmlrpc_request_call ; 
 scalar_t__ xmlrpc_request_response ; 

xml_element* DANDARPC_REQUEST_to_xml_element(XMLRPC_REQUEST request) {
   xml_element* wrapper = NULL;
   xml_element* root = NULL;
   if(request) {
      XMLRPC_REQUEST_TYPE request_type = XMLRPC_RequestGetRequestType(request);
      const char* pStr = NULL;
      xml_element_attr* version = emalloc(sizeof(xml_element_attr));
      version->key = estrdup(ATTR_VERSION);
      version->val = estrdup(VAL_VERSION_0_9);

      wrapper = xml_elem_new();

      if(request_type == xmlrpc_request_response) {
         pStr = ELEM_METHODRESPONSE;
      }
      else if(request_type == xmlrpc_request_call) {
         pStr = ELEM_METHODCALL;
      }
      if(pStr) {
         wrapper->name = estrdup(pStr);
      }

      root = xml_elem_new();
      root->name = estrdup(ELEM_ROOT);
      Q_PushTail(&root->attrs, version);
      Q_PushTail(&root->children, wrapper);

      pStr = XMLRPC_RequestGetMethodName(request);

      if(pStr) {
         xml_element* method = xml_elem_new();
         method->name = estrdup(ELEM_METHODNAME);
         simplestring_add(&method->text, pStr);
         Q_PushTail(&wrapper->children, method);
      }
      Q_PushTail(&wrapper->children,
                 DANDARPC_to_xml_element_worker(request, XMLRPC_RequestGetData(request)));
   }
   return root;
}