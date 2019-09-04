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
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST_INPUT_OPTIONS ;
typedef  TYPE_1__* XMLRPC_REQUEST ;
struct TYPE_4__ {int /*<<< orphan*/ * io; } ;

/* Variables and functions */
 TYPE_1__* XMLRPC_REQUEST_FromXML (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_RequestFree (TYPE_1__*,int /*<<< orphan*/ ) ; 

XMLRPC_VALUE XMLRPC_VALUE_FromXML (const char *in_buf, int len, XMLRPC_REQUEST_INPUT_OPTIONS in_options) {
   XMLRPC_VALUE xResponse = NULL;
   XMLRPC_REQUEST req = XMLRPC_REQUEST_FromXML(in_buf, len, in_options);

   if(req) {
      xResponse = req->io;
      XMLRPC_RequestFree(req, 0);
   }
   return xResponse;
}