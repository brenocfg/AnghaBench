#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* XMLRPC_REQUEST ;
struct TYPE_4__ {scalar_t__ error; scalar_t__ io; int /*<<< orphan*/  methodName; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_CleanupValue (scalar_t__) ; 
 int /*<<< orphan*/  my_free (TYPE_1__*) ; 
 int /*<<< orphan*/  simplestring_free (int /*<<< orphan*/ *) ; 

void XMLRPC_RequestFree(XMLRPC_REQUEST request, int bFreeIO) {
   if(request) {
      simplestring_free(&request->methodName);

      if(request->io && bFreeIO) {
         XMLRPC_CleanupValue(request->io);
      }
      if(request->error) {
         XMLRPC_CleanupValue(request->error);
      }
      my_free(request);
   }
}