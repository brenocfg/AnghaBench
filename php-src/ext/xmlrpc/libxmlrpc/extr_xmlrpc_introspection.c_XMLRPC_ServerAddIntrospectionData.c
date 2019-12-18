#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ desc; } ;
typedef  TYPE_1__ server_method ;
typedef  scalar_t__ XMLRPC_VALUE ;
typedef  TYPE_2__* XMLRPC_SERVER ;
struct TYPE_7__ {scalar_t__ xIntrospection; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_AddValueToVector (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_CleanupValue (scalar_t__) ; 
 scalar_t__ XMLRPC_CopyValue (scalar_t__) ; 
 scalar_t__ XMLRPC_CreateVector (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* XMLRPC_VectorGetStringWithID (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XMLRPC_VectorGetValueWithID (scalar_t__,char*) ; 
 scalar_t__ XMLRPC_VectorNext (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_VectorRemoveValue (scalar_t__,scalar_t__) ; 
 scalar_t__ XMLRPC_VectorRewind (scalar_t__) ; 
 TYPE_1__* find_method (TYPE_2__*,char const*) ; 
 scalar_t__ find_named_value (scalar_t__,char*) ; 
 int /*<<< orphan*/  xi_token_name ; 
 int /*<<< orphan*/  xmlrpc_vector_struct ; 

int XMLRPC_ServerAddIntrospectionData(XMLRPC_SERVER server, XMLRPC_VALUE desc) {
   int bSuccess = 0;
   if(server && desc) {
      XMLRPC_VALUE xNewTypes = XMLRPC_VectorGetValueWithID(desc, "typeList");
      XMLRPC_VALUE xNewMethods = XMLRPC_VectorGetValueWithID(desc, "methodList");
      XMLRPC_VALUE xServerTypes = XMLRPC_VectorGetValueWithID(server->xIntrospection, "typeList");

      if(xNewMethods) {
         XMLRPC_VALUE xMethod = XMLRPC_VectorRewind(xNewMethods);

         while(xMethod) {
            const char* name = XMLRPC_VectorGetStringWithID(xMethod, xi_token_name);
            server_method* sm = find_method(server, name);

            if(sm) {
               if(sm->desc) {
                  XMLRPC_CleanupValue(sm->desc);
               }
               sm->desc = XMLRPC_CopyValue(xMethod);
               bSuccess = 1;
            }

            xMethod = XMLRPC_VectorNext(xNewMethods);
         }
      }
      if(xNewTypes) {
         if(!xServerTypes) {
            if(!server->xIntrospection) {
               server->xIntrospection = XMLRPC_CreateVector(NULL, xmlrpc_vector_struct);
            }

            XMLRPC_AddValueToVector(server->xIntrospection, xNewTypes);
            bSuccess = 1;
         }
         else {
            XMLRPC_VALUE xIter = XMLRPC_VectorRewind(xNewTypes);
            while(xIter) {
               /* get rid of old values */
               XMLRPC_VALUE xPrev = find_named_value(xServerTypes, XMLRPC_VectorGetStringWithID(xIter, xi_token_name));
               if(xPrev) {
                  XMLRPC_VectorRemoveValue(xServerTypes, xPrev);
               }
               XMLRPC_AddValueToVector(xServerTypes, xIter);
               bSuccess = 1;
               xIter = XMLRPC_VectorNext(xNewTypes);
            }
         }
      }
   }
   return bSuccess;
}