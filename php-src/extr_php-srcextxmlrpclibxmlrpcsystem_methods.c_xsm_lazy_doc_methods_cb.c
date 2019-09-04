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
typedef  int /*<<< orphan*/  XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_CleanupValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_IntrospectionCreateDescription (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_ServerAddIntrospectionData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsm_introspection_xml ; 

__attribute__((used)) static void xsm_lazy_doc_methods_cb(XMLRPC_SERVER server, void* userData) {
   XMLRPC_VALUE xDesc = XMLRPC_IntrospectionCreateDescription(xsm_introspection_xml, NULL);
   XMLRPC_ServerAddIntrospectionData(server, xDesc);
   XMLRPC_CleanupValue(xDesc);
}