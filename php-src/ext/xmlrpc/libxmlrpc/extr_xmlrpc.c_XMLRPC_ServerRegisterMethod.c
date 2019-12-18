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
struct TYPE_6__ {int /*<<< orphan*/ * desc; scalar_t__ method; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ server_method ;
typedef  TYPE_2__* XMLRPC_SERVER ;
typedef  scalar_t__ XMLRPC_Callback ;
struct TYPE_7__ {int /*<<< orphan*/  methodlist; } ;

/* Variables and functions */
 int Q_PushTail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  estrdup (char const*) ; 

int XMLRPC_ServerRegisterMethod(XMLRPC_SERVER server, const char *name, XMLRPC_Callback cb) {
   if(server && name && cb) {

      server_method* sm = emalloc(sizeof(server_method));

      if(sm) {
         sm->name = estrdup(name);
         sm->method = cb;
         sm->desc = NULL;

         return Q_PushTail(&server->methodlist, sm);
      }
   }
   return 0;
}