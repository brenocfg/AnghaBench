#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * desc; } ;
typedef  TYPE_1__ server_method ;
typedef  scalar_t__ q_iter ;
typedef  scalar_t__ XMLRPC_VALUE_TYPE ;
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;
typedef  TYPE_2__* XMLRPC_SERVER ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST ;
struct TYPE_8__ {int /*<<< orphan*/  methodlist; int /*<<< orphan*/  xIntrospection; } ;

/* Variables and functions */
 TYPE_1__* Q_Iter_Get_F (scalar_t__) ; 
 scalar_t__ Q_Iter_Head_F (int /*<<< orphan*/ *) ; 
 scalar_t__ Q_Iter_Next_F (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_AddValueToVector (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_CreateVector (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_GetValueString (int /*<<< orphan*/ *) ; 
 scalar_t__ XMLRPC_GetValueType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_RequestGetData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XMLRPC_VectorGetValueWithID (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * XMLRPC_VectorNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_VectorRewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_docs_loaded (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  describe_method (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlrpc_string ; 
 scalar_t__ xmlrpc_vector ; 
 int /*<<< orphan*/  xmlrpc_vector_array ; 
 int /*<<< orphan*/  xmlrpc_vector_struct ; 

__attribute__((used)) static XMLRPC_VALUE xi_system_describe_methods_cb(XMLRPC_SERVER server, XMLRPC_REQUEST input, void* userData) {
   XMLRPC_VALUE xParams = XMLRPC_VectorRewind(XMLRPC_RequestGetData(input));
   XMLRPC_VALUE xResponse = XMLRPC_CreateVector(NULL, xmlrpc_vector_struct);
   XMLRPC_VALUE xMethodList = XMLRPC_CreateVector("methodList", xmlrpc_vector_array);
   XMLRPC_VALUE xTypeList = NULL;
   int bAll = 1;

   /* lazy loading of introspection data */
   check_docs_loaded(server, userData);

   xTypeList = XMLRPC_VectorGetValueWithID(server->xIntrospection, "typeList");

   XMLRPC_AddValueToVector(xResponse, xTypeList);
   XMLRPC_AddValueToVector(xResponse, xMethodList);

   /* check if we have any param */
   if(xParams) {
      /* check if string or vector (1 or n) */
      XMLRPC_VALUE_TYPE type = XMLRPC_GetValueType(xParams);
      if(type == xmlrpc_string) {
         /* just one.  spit it out. */
         describe_method(server, xMethodList, XMLRPC_GetValueString(xParams));
         bAll = 0;
      }
      else if(type == xmlrpc_vector) {
         /* multiple.  spit all out */
         XMLRPC_VALUE xIter = XMLRPC_VectorRewind(xParams);
         while(xIter) {
            describe_method(server, xMethodList, XMLRPC_GetValueString(xIter));
            xIter = XMLRPC_VectorNext(xParams);
         }
         bAll = 0;
      }
   }

   /* otherwise, default to sending all methods */
   if(bAll) {
      q_iter qi = Q_Iter_Head_F(&server->methodlist);
      while( qi ) {
         server_method* sm = Q_Iter_Get_F(qi);
         if(sm) {
            XMLRPC_AddValueToVector(xMethodList, sm->desc);
         }
         qi = Q_Iter_Next_F(qi);
      }
   }

   return xResponse;
}