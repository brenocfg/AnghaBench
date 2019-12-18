#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xml_element ;
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;
typedef  scalar_t__ XMLRPC_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/ * XMLRPC_RequestSetData (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_element_to_XMLRPC_REQUEST_worker (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

XMLRPC_VALUE xml_element_to_XMLRPC_REQUEST(XMLRPC_REQUEST request, xml_element* el)
{
   if (request) {
      return XMLRPC_RequestSetData(request, xml_element_to_XMLRPC_REQUEST_worker(request, NULL, NULL, el));
   }
   return NULL;
}