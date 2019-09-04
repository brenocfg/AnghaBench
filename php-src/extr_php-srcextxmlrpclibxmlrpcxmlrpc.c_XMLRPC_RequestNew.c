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
struct TYPE_4__ {int /*<<< orphan*/  methodName; } ;
typedef  int /*<<< orphan*/  STRUCT_XMLRPC_REQUEST ;

/* Variables and functions */
 TYPE_1__* ecalloc (int,int) ; 
 int /*<<< orphan*/  simplestring_init (int /*<<< orphan*/ *) ; 

XMLRPC_REQUEST XMLRPC_RequestNew() {
   XMLRPC_REQUEST xRequest = ecalloc(1, sizeof(STRUCT_XMLRPC_REQUEST));
   if(xRequest) {
      simplestring_init(&xRequest->methodName);
   }
   return xRequest;
}