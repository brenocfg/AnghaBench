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
typedef  int /*<<< orphan*/  XMLRPC_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_ServerRegisterIntrospectionCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_ServerRegisterMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xi_register_system_methods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsm_lazy_doc_methods_cb ; 
 int /*<<< orphan*/  xsm_system_get_capabilities_cb ; 
 int /*<<< orphan*/  xsm_system_multicall_cb ; 
 int /*<<< orphan*/  xsm_token_system_get_capabilities ; 
 int /*<<< orphan*/  xsm_token_system_multicall ; 

void xsm_register(XMLRPC_SERVER server) {
   xi_register_system_methods(server);

   XMLRPC_ServerRegisterMethod(server, xsm_token_system_multicall, xsm_system_multicall_cb);
   XMLRPC_ServerRegisterMethod(server, xsm_token_system_get_capabilities, xsm_system_get_capabilities_cb);

   /* callback for documentation generation should it be requested */
   XMLRPC_ServerRegisterIntrospectionCallback(server, xsm_lazy_doc_methods_cb);
}