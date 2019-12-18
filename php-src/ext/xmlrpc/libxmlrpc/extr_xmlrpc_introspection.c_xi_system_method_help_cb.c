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
struct TYPE_3__ {scalar_t__ desc; } ;
typedef  TYPE_1__ server_method ;
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_SERVER ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/ * XMLRPC_CreateValueString (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* XMLRPC_GetValueString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_RequestGetData (int /*<<< orphan*/ ) ; 
 char* XMLRPC_VectorGetStringWithID (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_VectorRewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_docs_loaded (int /*<<< orphan*/ ,void*) ; 
 TYPE_1__* find_method (int /*<<< orphan*/ ,char const*) ; 
 char const* xi_token_empty ; 
 int /*<<< orphan*/  xi_token_purpose ; 

__attribute__((used)) static XMLRPC_VALUE xi_system_method_help_cb(XMLRPC_SERVER server, XMLRPC_REQUEST input, void* userData) {
   const char* method = XMLRPC_GetValueString(XMLRPC_VectorRewind(XMLRPC_RequestGetData(input)));
   XMLRPC_VALUE xResponse = NULL;

   /* lazy loading of introspection data */
   check_docs_loaded(server, userData);

   if(method) {
      server_method* sm = find_method(server, method);
      if(sm && sm->desc) {
         const char* help = XMLRPC_VectorGetStringWithID(sm->desc, xi_token_purpose);

         /* returns a documentation string, or empty string */
         xResponse = XMLRPC_CreateValueString(NULL, help ? help : xi_token_empty, 0);
      }
   }

   return xResponse;
}