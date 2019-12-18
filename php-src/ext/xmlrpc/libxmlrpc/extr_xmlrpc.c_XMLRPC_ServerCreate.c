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
typedef  TYPE_1__* XMLRPC_SERVER ;
struct TYPE_5__ {int /*<<< orphan*/  docslist; int /*<<< orphan*/  methodlist; } ;
typedef  int /*<<< orphan*/  STRUCT_XMLRPC_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Q_Init (int /*<<< orphan*/ *) ; 
 TYPE_1__* ecalloc (int,int) ; 
 int /*<<< orphan*/  xsm_register (TYPE_1__*) ; 

XMLRPC_SERVER XMLRPC_ServerCreate() {
   XMLRPC_SERVER server = ecalloc(1, sizeof(STRUCT_XMLRPC_SERVER));
   if(server) {
      Q_Init(&server->methodlist);
      Q_Init(&server->docslist);

      /* register system methods */
      xsm_register(server);
   }
   return server;
}