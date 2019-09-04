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
typedef  int /*<<< orphan*/  XMLRPC_REQUEST_TYPE ;
typedef  TYPE_1__* XMLRPC_REQUEST ;
struct TYPE_3__ {int /*<<< orphan*/  request_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlrpc_request_none ; 

XMLRPC_REQUEST_TYPE XMLRPC_RequestGetRequestType(XMLRPC_REQUEST request) {
   return request ? request->request_type : xmlrpc_request_none;
}