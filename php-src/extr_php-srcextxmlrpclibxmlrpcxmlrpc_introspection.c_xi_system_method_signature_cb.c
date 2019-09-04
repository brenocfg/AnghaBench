#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * desc; } ;
typedef  TYPE_1__ server_method ;
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_SERVER ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_AddValueToVector (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_CreateValueString (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XMLRPC_CreateVector (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* XMLRPC_GetValueString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_RequestGetData (int /*<<< orphan*/ ) ; 
 char const* XMLRPC_VectorGetStringWithID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XMLRPC_VectorGetValueWithID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XMLRPC_VectorNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_VectorRewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_docs_loaded (int /*<<< orphan*/ ,void*) ; 
 TYPE_1__* find_method (int /*<<< orphan*/ ,char const*) ; 
 char const* type_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xi_token_params ; 
 int /*<<< orphan*/  xi_token_returns ; 
 int /*<<< orphan*/  xi_token_signatures ; 
 int /*<<< orphan*/  xi_token_type ; 
 int /*<<< orphan*/  xmlrpc_none ; 
 int /*<<< orphan*/  xmlrpc_vector_array ; 

__attribute__((used)) static XMLRPC_VALUE xi_system_method_signature_cb(XMLRPC_SERVER server, XMLRPC_REQUEST input, void* userData) {
   const char* method = XMLRPC_GetValueString(XMLRPC_VectorRewind(XMLRPC_RequestGetData(input)));
   XMLRPC_VALUE xResponse = NULL;

   /* lazy loading of introspection data */
   check_docs_loaded(server, userData);

   if(method) {
      server_method* sm = find_method(server, method);
      if(sm && sm->desc) {
         XMLRPC_VALUE xTypesArray = XMLRPC_CreateVector(NULL, xmlrpc_vector_array);
         XMLRPC_VALUE xIter, xParams, xSig, xSigIter;
         const char* type;

         /* array of possible signatures.  */
         xResponse = XMLRPC_CreateVector(NULL, xmlrpc_vector_array);

         /* find first signature */
         xSig = XMLRPC_VectorGetValueWithID(sm->desc, xi_token_signatures);
         xSigIter = XMLRPC_VectorRewind( xSig );

         /* iterate through sigs */
         while(xSigIter) {
            /* first type is the return value */
            type = XMLRPC_VectorGetStringWithID(XMLRPC_VectorRewind(
                                                 XMLRPC_VectorGetValueWithID(xSigIter, xi_token_returns)),
                                                xi_token_type);
            XMLRPC_AddValueToVector(xTypesArray,
                                    XMLRPC_CreateValueString(NULL,
                                                             type ? type : type_to_str(xmlrpc_none, 0),
                                    0));

            /* the rest are parameters */
            xParams = XMLRPC_VectorGetValueWithID(xSigIter, xi_token_params);
            xIter = XMLRPC_VectorRewind(xParams);

            /* iter through params, adding to types array */
            while(xIter) {
               XMLRPC_AddValueToVector(xTypesArray,
                                       XMLRPC_CreateValueString(NULL,
                                                                XMLRPC_VectorGetStringWithID(xIter, xi_token_type),
                                                                0));
               xIter = XMLRPC_VectorNext(xParams);
            }

            /* add types for this signature */
            XMLRPC_AddValueToVector(xResponse, xTypesArray);

            xSigIter = XMLRPC_VectorNext( xSig );
         }
      }
   }

   return xResponse;
}