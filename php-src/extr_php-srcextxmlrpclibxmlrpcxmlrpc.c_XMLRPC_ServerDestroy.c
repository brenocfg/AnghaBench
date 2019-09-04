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
struct TYPE_8__ {int /*<<< orphan*/  docslist; int /*<<< orphan*/  methodlist; scalar_t__ xIntrospection; scalar_t__ desc; struct TYPE_8__* name; } ;
typedef  TYPE_1__ server_method ;
typedef  TYPE_1__ doc_method ;
typedef  TYPE_1__* XMLRPC_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Q_Destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* Q_Head (int /*<<< orphan*/ *) ; 
 TYPE_1__* Q_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_CleanupValue (scalar_t__) ; 
 int /*<<< orphan*/  my_free (TYPE_1__*) ; 

void XMLRPC_ServerDestroy(XMLRPC_SERVER server) {
   if(server) {
      doc_method* dm = Q_Head(&server->docslist);
      server_method* sm = Q_Head(&server->methodlist);
      while( dm ) {
         my_free(dm);
         dm = Q_Next(&server->docslist);
      }
      while( sm ) {
         my_free(sm->name);
         if(sm->desc) {
            XMLRPC_CleanupValue(sm->desc);
         }
         my_free(sm);
         sm = Q_Next(&server->methodlist);
      }
      if (server->xIntrospection) {
         XMLRPC_CleanupValue(server->xIntrospection);
      }

      Q_Destroy(&server->methodlist);
      Q_Destroy(&server->docslist);
      my_free(server);
   }
}