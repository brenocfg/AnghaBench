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
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;
typedef  TYPE_1__* XMLRPC_REQUEST ;
struct TYPE_3__ {int /*<<< orphan*/ * io; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_CleanupValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_CopyValue (int /*<<< orphan*/ *) ; 

XMLRPC_VALUE XMLRPC_RequestSetData(XMLRPC_REQUEST request, XMLRPC_VALUE data) {
   if(request && data) {
		if (request->io) {
			XMLRPC_CleanupValue (request->io);
		}
      request->io = XMLRPC_CopyValue(data);
      return request->io;
   }
   return NULL;
}