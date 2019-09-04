#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ server_method ;
typedef  scalar_t__ q_iter ;
typedef  int /*<<< orphan*/  XMLRPC_VALUE ;
typedef  TYPE_2__* XMLRPC_SERVER ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST ;
struct TYPE_6__ {int /*<<< orphan*/  methodlist; } ;

/* Variables and functions */
 TYPE_1__* Q_Iter_Get_F (scalar_t__) ; 
 scalar_t__ Q_Iter_Head_F (int /*<<< orphan*/ *) ; 
 scalar_t__ Q_Iter_Next_F (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_CreateVector (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_VectorAppendString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlrpc_vector_array ; 

__attribute__((used)) static XMLRPC_VALUE xi_system_list_methods_cb(XMLRPC_SERVER server, XMLRPC_REQUEST input, void* userData) {
   XMLRPC_VALUE xResponse = XMLRPC_CreateVector(NULL, xmlrpc_vector_array);

   q_iter qi = Q_Iter_Head_F(&server->methodlist);
   while( qi ) {
      server_method* sm = Q_Iter_Get_F(qi);
      if(sm) {
         XMLRPC_VectorAppendString(xResponse, 0, sm->name, 0);
      }
      qi = Q_Iter_Next_F(qi);
   }
   return xResponse;
}